#include "MiniginPCH.h"
#include "Component.h"

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
