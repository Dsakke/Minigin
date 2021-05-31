#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
	: m_Active{true}
	, m_Components{}
{
}

dae::GameObject::~GameObject()
{
}

void dae::GameObject::Update()
{
	for (std::shared_ptr<Component> comp : m_Components)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<Component> comp : m_Components)
	{
		comp->Draw();
	}
}



void dae::GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->SetOwner(std::weak_ptr<GameObject>(shared_from_this()));
	m_Components.push_back(pComponent);
}

bool dae::GameObject::GetIsActive() const
{
	return m_Active;
}

void dae::GameObject::SetActive(bool active)
{
	m_Active = active;
}
