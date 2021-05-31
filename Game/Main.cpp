
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

	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("SandBox");


	std::shared_ptr<dae::FPSComponent> pFPS = std::make_shared<dae::FPSComponent>();

	dae::Transform transform{};
	transform.SetPosition(304, 100, 0);
	std::shared_ptr<LevelComponent> pLevel = LoadLevel("../data/level1.json", scene, transform);
	dae::ResourceManager& resourceManager = dae::ResourceManager::GetInstance();
	std::shared_ptr<dae::GameObject> pQbert = Factories::QBertFactory(pLevel, resourceManager.LoadTexture("qbert.png"));
	scene.Add(pQbert);

	std::weak_ptr<QBertComponent> pQbertComponent = pQbert->GetComponent<QBertComponent>();
	dae::InputAction moveUpAction{ std::make_shared<MoveUpCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadUp, SDL_SCANCODE_UP };
	inputManager.AddAction(std::move(moveUpAction));
	dae::InputAction moveDownAction{ std::make_shared<MoveDownCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadDown, SDL_SCANCODE_DOWN };
	inputManager.AddAction(std::move(moveDownAction));
	dae::InputAction moveLeftAction{ std::make_shared<MoveLeftCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadLeft, SDL_SCANCODE_LEFT };
	inputManager.AddAction(std::move(moveLeftAction));
	dae::InputAction moveRightAction{ std::make_shared<MoveRightCommand>(pQbertComponent), dae::InputType::keyDown, dae::ControllerButton::DPadRight, SDL_SCANCODE_RIGHT };
	inputManager.AddAction(std::move(moveRightAction));
	

	
}