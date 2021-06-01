#include "QbertComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include <stdexcept>
#include "LifeComponent.h"

QBertComponent::QBertComponent(std::weak_ptr<LevelComponent> pLevel)
	: m_pTransform{}
	, m_pLevelComponent{pLevel}
	, m_pLifeComponent{}
	, m_GridX{0}
	, m_GridY{0}
{
}

void QBertComponent::MoveLeft()
{
	--m_GridX;
	--m_GridY;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridX, m_GridY))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveRight()
{
	++m_GridX;
	++m_GridY;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridX, m_GridY))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveUp()
{
	--m_GridY;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridX, m_GridY))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::MoveDown()
{
	++m_GridY;
	if (auto pLevel = m_pLevelComponent.lock())
	{
		if (pLevel->FallsOfLevel(m_GridX, m_GridY))
		{
			FellOffGrid();
			return;
		}
	}
	MoveToNewPos();
}

void QBertComponent::Update()
{

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
	m_GridX = 0;
	m_GridY = 0;
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
		glm::vec2 pos = pLevel->GetTilePos(m_GridX, m_GridY);
		pTrans->SetPosition(pos.x, pos.y, 0);
	}
}
