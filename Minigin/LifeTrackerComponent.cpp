#include "MiniginPCH.h"
#include "LifeTrackerComponent.h"
#include "GameObject.h"
#include "QBertComponent.h"
#include "TextComponent.h"

LifeTrackerComponent::LifeTrackerComponent()
	: dae::Component()
	, dae::Observer()
{
}

void LifeTrackerComponent::Update()
{
}

void LifeTrackerComponent::Draw()
{
}

void LifeTrackerComponent::OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event)
{
	if (event == Events::QBertDied)
	{
		int nrLives{ pGameObject->GetComponent<QBertComponent>()->GetLives() };
		if (auto pOwner = m_pOwner.lock())
		{
			auto pTextComponent{ pOwner->GetComponent<dae::TextComponent>() };
			pTextComponent->SetText("Remaining lives: " + std::to_string(nrLives));

		}

	}
}
