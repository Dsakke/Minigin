
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
	


	dae::SoundLocator::ProvideSoundSystem(std::make_shared<dae::SoundSystem>());

	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("SandBox");

	dae::Transform transform{};
	transform.SetPosition(400, 100, 0);
	LoadLevel("../data/level1.json", scene, transform);
}