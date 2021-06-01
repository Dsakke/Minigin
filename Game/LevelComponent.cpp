#include "LevelComponent.h"
#include "LevelNodeComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"

LevelComponent::LevelComponent(Level&& level, int nodeSize)
	: m_Level{level}
	, m_TotalNodes{0}
	, m_ActiveNodes{0}
	, m_NodeSize{nodeSize}
{
	for (size_t i{}; i < level.size(); ++i)
	{
		m_TotalNodes += static_cast<int>(level[i].size());
	}
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
}

bool LevelComponent::FallsOfLevel(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return true;
	}
	// we can cast to unsigned here because negative numbers would already have exited the function
	if (static_cast<size_t>(y) >= m_Level.size())
	{
		return true;
	}
	// y already range checked
	if (static_cast<size_t>(x) >= m_Level[y].size())
	{
		return true;
	}
	return false;
}

void LevelComponent::StepOnTile(int x, int y)
{
	if (!FallsOfLevel(x, y))
	{
		std::shared_ptr<LevelNodeComponent> pNode =  m_Level[y][x];
		pNode->SteppedOn();
		if (m_ActiveNodes >= m_TotalNodes)
		{
			LevelWon();
		}
	}
}

glm::vec2 LevelComponent::GetTilePos(int x, int y) const
{
	if (!FallsOfLevel(x, y))
	{
		std::shared_ptr<LevelNodeComponent> pNode = m_Level[y][x];
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

}
