#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "TextComponent.h"
void dae::FPSComponent::Update()
{
	if (auto pOwner = m_pOwner.lock())
	{
		auto pTextComponent = pOwner->GetComponent<TextComponent>();
		pOwner->GetComponent<TextComponent>()->SetText(std::to_string(1 / Time::GetInstance()->GetElapsed()));
	}
}

void dae::FPSComponent::Draw()
{
}
