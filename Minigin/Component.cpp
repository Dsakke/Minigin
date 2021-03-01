#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetOwner(std::weak_ptr<GameObject> pOwner)
{
	m_pOwner = pOwner;
}
