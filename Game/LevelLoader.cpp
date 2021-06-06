#include "LevelLoader.h"
#include "LevelComponent.h"
#include "rapidjson.h"
#include "document.h"
#include "stream.h"
#include "filereadstream.h"
#include <stdexcept>
#include "LevelNodeComponent.h"
#include <vector>
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Transform.h"
#include <SDL.h>
#include "Factories.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "LifeComponent.h"
#include "InputManager.h"
#include "MoveDownCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveUpCommand.h"
#include "QbertComponent.h"
#include "ScoreComponent.h"
#include "EnemyManager.h"
#include "CoilyBehaviour.h"
#include "UggBehaviour.h"

std::shared_ptr<LevelComponent> LoadLevel(const std::string& file, const dae::Transform& transfrom)
{

    dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene(file);
    dae::ResourceManager& resourceManager = dae::ResourceManager::GetInstance();
    std::shared_ptr<dae::Font> pFont = resourceManager.LoadFont("Lingua.otf", 16);

    dae::InputManager& inputManager = scene.GetInputManager();

    // Create FPS Counter
    std::shared_ptr<dae::GameObject> pFPSObject = std::make_shared<dae::GameObject>();
    std::shared_ptr<dae::TextComponent> pFPSText = std::make_shared<dae::TextComponent>(pFont);
    std::shared_ptr<dae::FPSComponent> pFPS = std::make_shared<dae::FPSComponent>();
    std::shared_ptr<dae::TransformComponent> pFPSTransform = std::make_shared<dae::TransformComponent>(20.f, 10.f, 0.f);
    pFPSObject->AddComponent(pFPSTransform);
    pFPSObject->AddComponent(pFPSText);
    pFPSObject->AddComponent(pFPS);
    scene.Add(pFPSObject);



 // This code is based on an example given to me by Kristof (Don't know his last name)

    rapidjson::Document jsonDoc;
    FILE* pF = nullptr;
    // r stands for read, opening it with "r" will make it read only
    pF = _fsopen(file.c_str(), "r", _SH_DENYWR); // _SH_DENYWR means it will lock the file denying anything else writing writes while it is open
    

    if (!pF)
    {
        throw std::runtime_error(std::string("LoadLevel >> Textures must all have same dimensions"));
    }

    fseek(pF, 0, SEEK_END); // sets the file position to eof
    size_t fileSize = ftell(pF); // gives current file position in this case the last pos

    fseek(pF, 0, SEEK_SET); // sets the file position to the beginning of the file
    char* readBuffer = new char[fileSize];
    rapidjson::FileReadStream is(pF, readBuffer, sizeof(readBuffer));
    jsonDoc.ParseStream(is);

    delete[] readBuffer;
    fclose(pF);

// end of code based on example
    int size = jsonDoc["Size"].GetInt();
    LevelNodeComponent::NodeMode levelMode = static_cast<LevelNodeComponent::NodeMode>(jsonDoc["Level"].GetInt());
    std::shared_ptr<dae::Texture2D> pTextureNotActive = resourceManager.LoadTexture(std::string(jsonDoc["TextureNotActive"].GetString()));
    std::shared_ptr<dae::Texture2D> pTextureActive = resourceManager.LoadTexture(jsonDoc["TextureActive"].GetString());
    std::shared_ptr<dae::Texture2D> pTextureHalfActive{};

    int notActiveW, notActiveH, activeW, activeH, halfActiveW, halfActiveH;
    SDL_QueryTexture(pTextureNotActive->GetSDLTexture(), nullptr, nullptr, &notActiveW, &notActiveH);
    SDL_QueryTexture(pTextureActive->GetSDLTexture(), nullptr, nullptr, &activeW, &activeH);

    if (levelMode == LevelNodeComponent::NodeMode::level2)
    {
        pTextureHalfActive = resourceManager.LoadTexture(jsonDoc["TextureHalfActive"].GetString());
        SDL_QueryTexture(pTextureHalfActive->GetSDLTexture(), nullptr, nullptr, &halfActiveW, &halfActiveH);
        if (!((notActiveW == notActiveH) == (activeW == activeH) == (halfActiveW == halfActiveH)))
        {
            throw std::runtime_error(std::string("LoadLevel >> Textures must all have same dimensions"));
        }
    }
    else if(!((notActiveW == notActiveH) == (activeW == activeH)))
    {
        throw std::runtime_error(std::string("LoadLevel >> Textures must all have same dimensions"));
    }
    Level level{};

    for (int row{}; row < size; ++row)
    {
        level.push_back({});
        float posXStart{ transfrom.GetPosition().x - ((static_cast<float>(notActiveW) / 2.f) * row)  };
        for (int x{}; x < row + 1; ++x)
        {
            std::shared_ptr<dae::GameObject> pObject{};
            if (levelMode == LevelNodeComponent::NodeMode::level2)
            {
                pObject = Factories::LevelNodeFactory(pTextureNotActive, pTextureHalfActive, pTextureActive);
            }
            else
            {
                pObject = Factories::LevelNodeFactory(pTextureNotActive, pTextureActive, levelMode);
            }
            std::shared_ptr<dae::TransformComponent> pTransform = pObject->GetComponent<dae::TransformComponent>();
            float posX = posXStart + (notActiveW * x);
            float posY = transfrom.GetPosition().y + row * activeH * 0.75f;
            pTransform->SetPosition(posX, posY, 0);
            std::shared_ptr<LevelNodeComponent> pNode = pObject->GetComponent<LevelNodeComponent>();
            level[row].push_back(pNode);
            scene.Add(pObject);
        }
    }
    std::shared_ptr<LevelComponent> pLevelComp = std::make_shared<LevelComponent>(std::move(level), notActiveW);
    std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();
    pObject->AddComponent(pLevelComp);
    scene.Add(pObject);

    std::shared_ptr<EnemyManager> pEnemyManager = std::make_shared<EnemyManager>(10, scene, pLevelComp, 5.f);
    std::shared_ptr<dae::GameObject> pEnemyManagerObject = std::make_shared<dae::GameObject>();



    // Create QBert
    std::shared_ptr<dae::GameObject> pQbert = Factories::QBertFactory(pLevelComp, pEnemyManager,resourceManager.LoadTexture("qbert.png"));
    std::shared_ptr<dae::Texture2D> pFullheart = resourceManager.LoadTexture("heart.png");
    std::shared_ptr<dae::Texture2D> pEmptyheart = resourceManager.LoadTexture("heartEmpty.png");
    std::shared_ptr<LifeComponent> pLife = std::make_shared<LifeComponent>(scene, glm::vec2{ 20, 40 }, pEmptyheart, pFullheart);
    pQbert->AddComponent(pLife);
    scene.Add(pQbert);

    // Create Inputs
    std::shared_ptr<QBertComponent> pQbertComponent = pQbert->GetComponent<QBertComponent>();
    dae::InputAction moveUpAction{ std::make_shared<MoveUpCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadUp, SDL_SCANCODE_UP };
    inputManager.AddAction(std::move(moveUpAction));
    dae::InputAction moveDownAction{ std::make_shared<MoveDownCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadDown, SDL_SCANCODE_DOWN };
    inputManager.AddAction(std::move(moveDownAction));
    dae::InputAction moveLeftAction{ std::make_shared<MoveLeftCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadLeft, SDL_SCANCODE_LEFT };
    inputManager.AddAction(std::move(moveLeftAction));
    dae::InputAction moveRightAction{ std::make_shared<MoveRightCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadRight, SDL_SCANCODE_RIGHT };
    inputManager.AddAction(std::move(moveRightAction));


    // Create Score
    std::shared_ptr<dae::GameObject> pScoreObject = Factories::ScoreFactory(pFont);
    scene.Add(pScoreObject);
    std::weak_ptr<ScoreComponent> pScore = pScoreObject->GetComponent<ScoreComponent>();
    std::shared_ptr<dae::TransformComponent> pScoreTransform = pScoreObject->GetComponent<dae::TransformComponent>();
    pScoreTransform->SetPosition(20.f, 60.f, 0.f);
    pQbertComponent->AddObserver(pScore);

    pLevelComp->AddScoreObserver(pScore);

    // Add Enemies
    std::unique_ptr<CoilyBehaviour> pCoilyBehaviour = std::make_unique<CoilyBehaviour>(pQbertComponent, dae::ResourceManager::GetInstance().LoadTexture("Egg.png"), dae::ResourceManager::GetInstance().LoadTexture("Heart.png"));
    pEnemyManager->AddEnemy(std::move(pCoilyBehaviour), dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));
    pEnemyManagerObject->AddComponent(pEnemyManager);
    scene.Add(pEnemyManagerObject);

    std::unique_ptr<UggBehaviour> pUggBehaviour = std::make_unique<UggBehaviour>(true);
    pEnemyManager->AddEnemy(std::move(pUggBehaviour), dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));
    std::unique_ptr<UggBehaviour> pWrongWayBehaviour = std::make_unique<UggBehaviour>(false);
    pEnemyManager->AddEnemy(std::move(pWrongWayBehaviour), dae::ResourceManager::GetInstance().LoadTexture("Egg.png"));

    return pLevelComp;
}
