#include "LevelComponent.h"
#include "LevelNodeComponent.h"

LevelComponent::LevelComponent(Level&& level)
	: m_Level{level}
	, m_TotalNodes{0}
	, m_ActiveNodes{0}
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

Level& LevelComponent::GetLevel()
{
	return m_Level;
}

void LevelComponent::LevelWon()
{

}
