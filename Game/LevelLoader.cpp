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

std::shared_ptr<LevelComponent> LoadLevel(const std::string& file, dae::Scene& scene, const dae::Transform& transfrom)
{
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
    dae::ResourceManager& resourceManager = dae::ResourceManager::GetInstance();
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
    Level& l = pLevelComp->GetLevel();
    for (int row{}; row < size; ++row)
    {
        for (int x{}; x < row + 1; ++x)
        {
            l[row][x]->AddObserver(pLevelComp);
        }
    }
    scene.Add(pObject);
    return pLevelComp;
}
