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
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "ExitCommand.h"
#include "ToggleDebugWindowCommand.h"

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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	
	auto pSpriteRenderer{ new SpriteRenderComponent{ResourceManager::GetInstance().LoadTexture("background.jpg")} };
	go->AddComponent(pSpriteRenderer);
	auto pBGTransform{ new TransformComponent{} };
	pBGTransform->SetPosition(0, 0, 0);
	go->AddComponent(pBGTransform);
	scene.Add(go);


	go = std::make_shared<GameObject>();
	pSpriteRenderer = new SpriteRenderComponent{ ResourceManager::GetInstance().LoadTexture("logo.png") };
	go->AddComponent(pSpriteRenderer);
	auto pLogoTransform{ new TransformComponent{} };
	pLogoTransform->SetPosition(210, 180, 0);
	go->AddComponent(pLogoTransform);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTextObject = std::make_shared<GameObject>();
	auto pTextComponentTransform{ new TransformComponent{} };
	pTextComponentTransform->SetPosition(80, 20, 0);
	pTextObject->AddComponent(pTextComponentTransform);
	auto pTextComponent{ new TextComponent{" ", font} };
	pTextObject->AddComponent(pTextComponent);
	auto pFpsComponent{ new FPSComponent{} };
	pTextObject->AddComponent(pFpsComponent);
	scene.Add(pTextObject);
	
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
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;

		dae::InputAction exitAction{};
		exitAction.controllerButton = dae::ControllerButton::Start;
		exitAction.pCommand = new ExitCommand(doContinue);
		exitAction.inputType = dae::InputType::keyDown;
		input.AddAction(std::move(exitAction));

		InputAction toggleWindowAction{};
		toggleWindowAction.controllerButton = dae::ControllerButton::ButtonA;
		toggleWindowAction.inputType = dae::InputType::keyDown;
		toggleWindowAction.pCommand = new ToggleDebugCommand();
		input.AddAction(std::move(toggleWindowAction));


		while (doContinue)
		{
			Time::GetInstance()->UpdateTime();
			const auto currentTime = high_resolution_clock::now();
			
			input.ProcessInput();
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
