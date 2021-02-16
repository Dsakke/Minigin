#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;
}
