#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include <stdexcept>

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
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
