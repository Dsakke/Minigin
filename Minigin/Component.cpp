#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"
dae::Component::Component()
	: m_pOwner{}
	, m_IsInitialized{}
{
}

void dae::Component::RootUpdate()
{
	if (!m_IsInitialized)
	{
		RootInitialize();
	}
	if (m_pOwner.lock()->GetIsActive())
	{
		Update();
	}
}

void dae::Component::RootInitialize()
{
	Initialize();
	m_IsInitialized = true;
}

void dae::Component::SetOwner(std::weak_ptr<GameObject> pOwner)
{
	m_pOwner = pOwner;
}

std::weak_ptr<dae::GameObject> dae::Component::GetGameObject()
{
	return m_pOwner;
}

const std::weak_ptr<dae::GameObject> dae::Component::GetGameObject() const
{
	return m_pOwner;
}
