#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

ScoreComponent::ScoreComponent()
	: m_EventScoreIncrements{}
	, m_Score{0}
{
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::ColorChange, 25});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::CoilyDefeatedFlyingDisc, 500});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::DiscRemained, 50});
	m_EventScoreIncrements.insert(std::pair<Events, int>{Events::SamOrSlickCaught, 300});
}

void ScoreComponent::OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event)
{
	auto it = m_EventScoreIncrements.find(event);
	if (it != m_EventScoreIncrements.end())
	{
		m_Score += it->second;
		if (auto pOwner = m_pOwner.lock())
		{
			auto pTextComponent = pOwner->GetComponent<dae::TextComponent>();
			if (pTextComponent)
			{
				pTextComponent->SetText("Score: " + std::to_string(m_Score));
			}
			else
			{
				throw std::runtime_error("ScoreComponent was notified while attached to a GameObject without a TextComponent");
			}
		}
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
}
