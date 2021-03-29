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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	
	SoundLocator::ProvideSoundSystem(std::make_shared<SoundSystemLogger>(std::make_shared<SoundSystem>()));

	auto pSpriteRenderer{ std::make_shared<SpriteRenderComponent>(ResourceManager::GetInstance().LoadTexture("background.jpg")) };
	go->AddComponent(pSpriteRenderer);
	auto pBGTransform{ std::make_shared<TransformComponent>() };
	pBGTransform->SetPosition(0, 0, 0);
	go->AddComponent(pBGTransform);
	scene.Add(go);


	go = std::make_shared<GameObject>();
	pSpriteRenderer = std::make_shared<SpriteRenderComponent>( ResourceManager::GetInstance().LoadTexture("logo.png") );
	go->AddComponent(pSpriteRenderer);
	auto pLogoTransform{ std::make_shared<TransformComponent>() };
	pLogoTransform->SetPosition(210, 180, 0);
	go->AddComponent(pLogoTransform);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTextObject = std::make_shared<GameObject>();
	auto pTextComponentTransform{ std::make_shared<TransformComponent>(TransformComponent{80, 20, 0}) };
	pTextObject->AddComponent(pTextComponentTransform);
	auto pTextComponent{ std::make_shared<TextComponent>(font) };
	pTextObject->AddComponent(pTextComponent);
	auto pFpsComponent{ std::make_shared<FPSComponent>() };
	pTextObject->AddComponent(pFpsComponent);
	scene.Add(pTextObject);

	auto pLiveDisplay = std::make_shared<GameObject>();
	auto pLiveComponent = std::make_shared<LifeTrackerComponent>();
	pLiveDisplay->AddComponent(pLiveComponent);
	auto pLiveTextComponent = std::make_shared<TextComponent>( font );
	pLiveDisplay->AddComponent(pLiveTextComponent);
	auto pLiveTransformComponent{ std::make_shared<TransformComponent>(TransformComponent{300, 20, 0}) };
	pLiveDisplay->AddComponent(pLiveTransformComponent);
	scene.Add(pLiveDisplay);

	auto pScoreDisplay = std::make_shared<GameObject>();
	auto pScoreComponent = std::make_shared<ScoreComponent>();
	auto pScoreTransform = std::make_shared<TransformComponent>(TransformComponent{ 300, 200, 0 });
	auto pScoreText = std::make_shared<TextComponent>(font);
	pScoreDisplay->AddComponent(pScoreComponent);
	pScoreDisplay->AddComponent(pScoreTransform);
	pScoreDisplay->AddComponent(pScoreText);
	scene.Add(pScoreDisplay);

	auto pQbertObject = std::make_shared<GameObject>();
	auto pQBertComponent{ std::make_shared<QBertComponent>() };
	pQBertComponent->AddObserver(pLiveComponent);
	pQBertComponent->AddObserver(pScoreComponent);
	pQbertObject->AddComponent(pQBertComponent);
	scene.Add(pQbertObject);


	auto pLiveDisplay2 = std::make_shared<GameObject>();
	auto pLiveComponent2 = std::make_shared<LifeTrackerComponent>();
	pLiveDisplay2->AddComponent(pLiveComponent2);
	auto pLiveTextComponent2 = std::make_shared<TextComponent>(font);
	pLiveDisplay2->AddComponent(pLiveTextComponent2);
	auto pLiveTransformComponent2{ std::make_shared<TransformComponent>(TransformComponent{80, 80, 0}) };
	pLiveDisplay2->AddComponent(pLiveTransformComponent2);
	scene.Add(pLiveDisplay2);

	auto pScoreDisplay2 = std::make_shared<GameObject>();
	auto pScoreComponent2 = std::make_shared<ScoreComponent>();
	auto pScoreTransform2 = std::make_shared<TransformComponent>(TransformComponent{ 80, 200, 0 });
	auto pScoreText2 = std::make_shared<TextComponent>(font);
	pScoreDisplay2->AddComponent(pScoreComponent2);
	pScoreDisplay2->AddComponent(pScoreTransform2);
	pScoreDisplay2->AddComponent(pScoreText2);
	scene.Add(pScoreDisplay2);

	auto pQbertObject2 = std::make_shared<GameObject>();
	auto pQBertComponent2{ std::make_shared<QBertComponent>() };
	pQBertComponent2->AddObserver(pLiveComponent2);
	pQBertComponent2->AddObserver(pScoreComponent2);
	pQbertObject->AddComponent(pQBertComponent2);
	scene.Add(pQbertObject2);

	// Add inputs
	auto& input = InputManager::GetInstance();
	InputAction dieAction{ std::make_shared<DiedCommand>(pQBertComponent), dae::InputType::keyDown, dae::ControllerButton::ButtonB, -1 };
	input.AddAction(std::move(dieAction));

	InputAction gainScoreAction{ std::make_shared<GainScoreCommand>(pQBertComponent), dae::InputType::keyDown, dae::ControllerButton::ButtonA, -1 };
	input.AddAction(std::move(gainScoreAction));

	InputAction dieAction2{ std::make_shared<DiedCommand>(pQBertComponent2), dae::InputType::keyDown, dae::ControllerButton::ButtonX, -1 };
	input.AddAction(std::move(dieAction2));


	InputAction soundTestAction{ std::make_shared<SoundTestCommand>(), dae::InputType::keyDown, dae::ControllerButton::ButtonY, -1 };
	input.AddAction(std::move(soundTestAction));
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



		InputAction toggleWindowAction{ std::make_shared<ToggleDebugCommand>(), dae::InputType::keyDown, dae::ControllerButton::Back, 65 };
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
