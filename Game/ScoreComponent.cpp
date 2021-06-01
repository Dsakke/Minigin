#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

int ScoreComponent::m_Score{ 0 };

ScoreComponent::ScoreComponent()
	: m_EventScoreIncrements{}
{
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::LevelNodeActivated, 25});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::CoilyDefeatedFlyingDisc, 500});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::DiscRemained, 50});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::SamOrSlickCaught, 300});
}

void ScoreComponent::ResetScore()
{
	m_Score = 0;
}


void ScoreComponent::OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event)
{
	auto it = m_EventScoreIncrements.find(event);
	if (it != m_EventScoreIncrements.end())
	{
		m_Score += it->second;
		m_pTextComponent->SetText("Score: " + std::to_string(m_Score));
	}
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Draw()
{
}

void ScoreComponent::Initialize()
{
	if (auto pOwner = m_pOwner.lock())
	{
		auto pTextComponent = pOwner->GetComponent<dae::TextComponent>();
		if (!pTextComponent)
		{
			throw std::runtime_error("ScoreComponent attached to GameObject without TextComponent");
		}
		else
		{
			m_pTextComponent = pTextComponent;
			m_pTextComponent->SetText("Score: " + m_Score);
		}
	}
}
