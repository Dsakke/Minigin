#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

const std::string& dae::Scene::GetName() const
{
	return m_Name;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		if (object->GetIsActive())
		{
			object->Update();
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (object->GetIsActive())
		{
			object->Render();
		}
	}
}

