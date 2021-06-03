
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
#include "Transform.h"
#include "LevelLoader.h"
#include "LevelSwitcher.h"

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
	dae::SoundLocator::ProvideSoundSystem(std::make_shared<dae::SoundSystem>());


	std::string level1{ "../data/level1.json" };
	std::string level2{ "../data/level2.json" };
	std::string level3{ "../data/level3.json" };

	dae::SceneManager::GetInstance().CreateScene("GameOver");
	dae::SceneManager::GetInstance().CreateScene("Start");
	// Load Level
	dae::Transform transform{};
	transform.SetPosition(304, 100, 0);
	std::shared_ptr<LevelComponent> pLevel1 = LoadLevel(level1, transform);
	std::shared_ptr<LevelComponent> pLevel2 = LoadLevel(level2, transform);
	std::shared_ptr<LevelComponent> pLevel3 = LoadLevel(level3, transform);

	LevelSwitcher& levelSwitcher = LevelSwitcher::GetInstance();
	levelSwitcher.AddLevel(level1);
	levelSwitcher.AddLevel(level2);
	levelSwitcher.AddLevel(level3);
	levelSwitcher.LoadFirstLevel();

	levelSwitcher.SetStartMenu("Start");
	levelSwitcher.SetGameOver("GameOver");
	
	

}