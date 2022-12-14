#include "LevelComponent.h"
#include "LevelNodeComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"
#include "LevelSwitcher.h"

LevelComponent::LevelComponent(Level&& level, int nodeSize)
	: m_Level{level}
	, m_TotalNodes{0}
	, m_ActiveNodes{0}
	, m_NodeSize{nodeSize}
{

}

void LevelComponent::OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event)
{
	switch (event)
	{
	case Events::LevelNodeActivated:
		++m_ActiveNodes;
		if (m_ActiveNodes == m_TotalNodes)
		{
			LevelWon();
		}
		break;
	case Events::LevelNodeDeactivated:
		--m_ActiveNodes;
		break;
	default:
		break;
	}
}

void LevelComponent::Draw()
{
}

void LevelComponent::Update()
{
}

void LevelComponent::Initialize()
{
	for (size_t i{}; i < m_Level.size(); ++i)
	{
		m_TotalNodes += static_cast<int>(m_Level[i].size());
		for (size_t node{}; node < m_Level[i].size(); ++node)
		{
			m_Level[i][node]->AddObserver(shared_from_this());
		}
	}
}

bool LevelComponent::FallsOfLevel(const glm::ivec2& coords) const
{
	if (coords.x < 0 || coords.y < 0)
	{
		return true;
	}
	// we can cast to unsigned here because negative numbers would already have exited the function
	if (static_cast<size_t>(coords.y) >= m_Level.size())
	{
		return true;
	}
	// y already range checked
	if (static_cast<size_t>(coords.x) >= m_Level[coords.y].size())
	{
		return true;
	}
	return false;
}

void LevelComponent::StepOnTile(const glm::ivec2& coords)
{
	if (!FallsOfLevel(coords))
	{
		std::shared_ptr<LevelNodeComponent> pNode =  m_Level[coords.y][coords.x];
		pNode->SteppedOn();
	}
}

glm::vec2 LevelComponent::GetTilePos(const glm::ivec2& coords) const
{
	if (!FallsOfLevel(coords))
	{
		std::shared_ptr<LevelNodeComponent> pNode = m_Level[coords.y][coords.x];
		if (auto pObject = pNode->GetGameObject().lock())
		{
			auto pTransform = pObject->GetComponent<dae::TransformComponent>();
			auto& pos = pTransform->GetTransform().GetPosition();
			return glm::vec2{ pos.x + m_NodeSize / 4, pos.y - m_NodeSize / 2};
		}
	}
	return glm::vec2();
}

Level& LevelComponent::GetLevel()
{
	return m_Level;
}

int LevelComponent::GetNodeSize() const
{
	return m_NodeSize;
}

void LevelComponent::AddScoreObserver(std::weak_ptr<ScoreComponent> pScore)
{
	for (std::vector<std::shared_ptr<LevelNodeComponent>> row : m_Level)
	{
		for (std::shared_ptr<LevelNodeComponent> pNode : row)
		{
			pNode->AddObserver(pScore);
		}
	}
}

void LevelComponent::LevelWon()
{
	LevelSwitcher::GetInstance().LoadNextlevel();
}
