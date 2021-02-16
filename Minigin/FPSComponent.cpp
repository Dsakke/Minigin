#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "TextComponent.h"
void dae::FPSComponent::Update()
{
	m_pOwner->GetComponent<TextComponent>()->SetText(std::to_string(1 / Time::GetInstance()->GetElapsed()));
}

void dae::FPSComponent::Draw()
{
}
