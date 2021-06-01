#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "TextComponent.h"
void dae::FPSComponent::Update()
{
	if (auto pOwner = m_pOwner.lock())
	{
		auto pTextComponent = pOwner->GetComponent<TextComponent>();
		if (pTextComponent)
		{
			pOwner->GetComponent<TextComponent>()->SetText(std::to_string(1 / Time::GetInstance()->GetElapsed()));
		}
		else
		{
			throw std::runtime_error("FPSComponent is attached to a GameObject without a TextComponent");
		}
	}
}

void dae::FPSComponent::Draw()
{
}

void dae::FPSComponent::Initialize()
{
}
