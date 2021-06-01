
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif
#include <Windows.h>
#include "SDL.h"
#include "Minigin.h"
#include "SoundSystem.h"
#include "SoundLocator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Factories.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "LevelComponent.h"
#include "Transform.h"
#include "QbertComponent.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "LifeComponent.h"
#include "ScoreComponent.h"

void LoadGame();

int main(int, char* []) 
{
	dae::Minigin engine;
	engine.Initialize();
	LoadGame();
	engine.Run();




	return 0;
}

void LoadGame()
{
	//dae::InputManager& inputManager = dae::InputManager::GetInstance();
	
	dae::InputManager& inputManager = dae::InputManager::GetInstance();
	dae::SoundLocator::ProvideSoundSystem(std::make_shared<dae::SoundSystem>());
	dae::ResourceManager& resourceManager = dae::ResourceManager::GetInstance();

	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("SandBox");
	dae::SceneManager::GetInstance().SetCurrentScene("SandBox");
	std::shared_ptr<dae::Font> pFont = resourceManager.LoadFont("Lingua.otf", 16);
	
	// Create FPS Counter
	std::shared_ptr<dae::GameObject> pFPSObject = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextComponent> pFPSText = std::make_shared<dae::TextComponent>(pFont);
	std::shared_ptr<dae::FPSComponent> pFPS = std::make_shared<dae::FPSComponent>();
	std::shared_ptr<dae::TransformComponent> pFPSTransform = std::make_shared<dae::TransformComponent>(20.f, 10.f, 0.f);
	pFPSObject->AddComponent(pFPSTransform);
	pFPSObject->AddComponent(pFPSText);
	pFPSObject->AddComponent(pFPS);
	scene.Add(pFPSObject);

	// Load Level
	dae::Transform transform{};
	transform.SetPosition(304, 100, 0);
	std::shared_ptr<LevelComponent> pLevel = LoadLevel("../data/level1.json", scene, transform);
	std::shared_ptr<dae::GameObject> pQbert = Factories::QBertFactory(pLevel, resourceManager.LoadTexture("qbert.png"));

	// Create QBert
	std::shared_ptr<dae::Texture2D> pFullheart = resourceManager.LoadTexture("heart.png");
	std::shared_ptr<dae::Texture2D> pEmptyheart = resourceManager.LoadTexture("heartEmpty.png");
	std::shared_ptr<LifeComponent> pLife = std::make_shared<LifeComponent>(scene, glm::vec2{20, 40}, pEmptyheart, pFullheart);
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

	pLevel->AddScoreObserver(pScore);
}