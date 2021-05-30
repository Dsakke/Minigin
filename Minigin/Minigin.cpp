#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TimeManager.h"
#include "SpriteRenderComponent.h"
#include "ExitCommand.h"
#include "ToggleDebugWindowCommand.h"
#include "QBertComponent.h"
#include "LifeTrackerComponent.h"
#include "DiedCommand.h"
#include "ScoreComponent.h"
#include "GainScoreCommand.h"
#include "SoundLocator.h"
#include "SoundSystem.h"
#include "SoundSystemLogger.h"
#include "SoundTestCommand.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Time::DestroyInstance();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		
		bool doContinue = true;



		InputAction toggleWindowAction{ std::make_shared<ToggleDebugCommand>(), dae::InputType::keyDown, dae::ControllerButton::Back, SDL_SCANCODE_SPACE };
		input.AddAction(std::move(toggleWindowAction));


		while (doContinue)
		{
			Time::GetInstance()->UpdateTime();
			const auto currentTime = high_resolution_clock::now();
			
			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			if (sleepTime.count() > 0)
			{
				this_thread::sleep_for(sleepTime);
			}
		}
	}

	Cleanup();
}
