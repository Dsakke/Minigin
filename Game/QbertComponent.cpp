#include "QbertComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include <stdexcept>
#include "LifeComponent.h"
#include "EnemyManager.h"
#include "EnemyComponent.h"

QBertComponent::QBertComponent(std::weak_ptr<LevelComponent> pLevel, std::weak_ptr<EnemyManager> pEnemyManager)
	: m_pTransform{}
	, m_pLevelComponent{pLevel}
	, m_pLifeComponent{}
	, m_pEnemyManager{pEnemyManager}
	, m_GridCoords{0,0}
{
}

void QBertComponent::MoveLeft()
{
	--m_GridCoords.x;
	--m_GridCoords.y;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridCoords))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveRight()
{
	++m_GridCoords.x;
	++m_GridCoords.y;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridCoords))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveUp()
{
	--m_GridCoords.y;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridCoords))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveDown()
{
	++m_GridCoords.y;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridCoords))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::Update()
{
	if (auto pEnemyManager = m_pEnemyManager.lock())
	{
		std::shared_ptr<EnemyComponent> pEnemy = pEnemyManager->GetOverlapping(m_GridCoords);
		if (pEnemy)
		{
			if (pEnemy->GetIsharmfull())
			{
				pEnemyManager->Reset();
				if (auto pLife = m_pLifeComponent.lock())
				{
					pLife->LoseLife();
				}
			}
		}
	}
}

void QBertComponent::Draw()
{
}

void QBertComponent::Initialize()
{
	auto pLife = m_pLifeComponent.lock();
	if (!pLife)
	{
		if (auto pOwner = m_pOwner.lock())
		{
			pLife = pOwner->GetComponent<LifeComponent>();
			m_pLifeComponent = pLife;
		}
		else
		{
			throw std::runtime_error(std::string("QBertComponent::Update >> QBertComponent attached to GameObject without LifeComponent"));
		}
	}
	if (!m_pTransform.lock())
	{
		if (auto pOwner = m_pOwner.lock())
		{
			std::shared_ptr<dae::TransformComponent> pTrans = pOwner->GetComponent<dae::TransformComponent>();
			if (pTrans)
			{
				m_pTransform = pTrans;
			}
			else
			{
				throw std::runtime_error(std::string("QBertComponent::Update >> QBertComponent attached to GameObject without TransformComponent"));
			}
		}
	}
}

void QBertComponent::FellOffGrid()
{
	m_GridCoords = glm::ivec2{ 0,0 };
	MoveToNewPos();
	auto pLife = m_pLifeComponent.lock();
	pLife->LoseLife();
	
}

void QBertComponent::MoveToNewPos()
{
	auto pTrans = m_pTransform.lock();
	auto pLevel = m_pLevelComponent.lock();
	if (pTrans && pLevel)
	{
		glm::vec2 pos = pLevel->GetTilePos(m_GridCoords);
		pTrans->SetPosition(pos.x, pos.y, 0);
		pLevel->StepOnTile(m_GridCoords);
	}
}
