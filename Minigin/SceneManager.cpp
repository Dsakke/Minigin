#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include <stdexcept>

void dae::SceneManager::SetCurrentScene(const std::string name)
{
	auto pred = [=](const std::shared_ptr<Scene>& scene) { return scene->GetName() == name; };
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), pred);
	if (it != m_Scenes.end())
	{
		m_pCurrentScene = *it;
	}
}

void dae::SceneManager::Update()
{
	m_pCurrentScene->Update();
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	auto pred = [=](const std::shared_ptr<Scene>& scene) { return scene->GetName() == name; };
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), pred);
	if (it != m_Scenes.end())
	{
		return **it;
	}
	return CreateScene(name);
}

dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_pCurrentScene;
}
