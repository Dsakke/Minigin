#include "MiniginPCH.h"
#include "QBertComponent.h"

QBertComponent::QBertComponent()
	: m_Lives{3}
{
}

void QBertComponent::Die()
{
	if (auto pOwner = m_pOwner.lock())
	{
		--m_Lives;
		Notify(pOwner, Events::QBertDied);
	}
}

void QBertComponent::Update()
{
}

void QBertComponent::Draw()
{
}

int QBertComponent::GetLives() const
{
	return m_Lives;
}
