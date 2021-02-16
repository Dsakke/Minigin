#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (Component* pComp : m_Components)
	{
		delete pComp;
	}
}

void dae::GameObject::Update()
{
	for (Component* comp : m_Components)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (Component* comp : m_Components)
	{
		comp->Draw();
	}
}



void dae::GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	m_Components.push_back(pComponent);
}
