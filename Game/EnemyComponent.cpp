#include "EnemyComponent.h"
#include "LevelComponent.h"
#include "IEnemyBehaviour.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include "TimeManager.h"

EnemyComponent::EnemyComponent(std::weak_ptr<LevelComponent> pLevelComponent, std::unique_ptr<IEnemyBehaviour>&& pBehaviour, float moveTime)
	: m_GridCoords{ 0, 0 }
	, m_pBehaviour{std::move(pBehaviour)}
	, m_pSpriteRenderer{}
	, m_pTransform{}
	, m_pLevelComponent{pLevelComponent}
	, m_MoveTime{moveTime}
	, m_Timer{0.f}

{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Update()
{
	m_Timer += dae::Time::GetInstance()->GetElapsed();
	if (m_Timer >= m_MoveTime)
	{
		m_Timer = 0.f;
		Move();
	}
}

void EnemyComponent::Draw()
{
}

void EnemyComponent::Initialize()
{
	std::shared_ptr<dae::GameObject> pOwner = m_pOwner.lock();
	if (!pOwner)
	{
		throw std::runtime_error("EnemyComponent::Initialize >> Initialized without being attached to GameObject");
	}

	m_pSpriteRenderer = pOwner->GetComponent<dae::SpriteRenderComponent>();
	if (!m_pSpriteRenderer)
	{
		throw std::runtime_error("EnemyComponent::Initialize >> Initialized without SpriteRenderComponent attached to object");
	}

	m_pTransform = pOwner->GetComponent<dae::TransformComponent>();
	if (!m_pTransform)
	{
		throw std::runtime_error("EnemyComponent::Initialize >> Initialized without TransformComponent attached to object");
	}
}

void EnemyComponent::Move()
{
	(*m_pBehaviour)(m_GridCoords, m_pLevelComponent);
	if (auto pLevel = m_pLevelComponent.lock())
	{
		glm::vec2 pos = pLevel->GetTilePos(m_GridCoords);
		m_pTransform->SetPosition(pos.x, pos.y, 0);
	}
}

void EnemyComponent::Reset()
{
	m_pBehaviour->SetStartPos(m_GridCoords);
	if (auto pLevel = m_pLevelComponent.lock())
	{
		glm::vec2 pos = pLevel->GetTilePos(m_GridCoords);
		m_pTransform->SetPosition(pos.x, pos.y, 0);
	}

}

void EnemyComponent::SetState(std::unique_ptr<IEnemyBehaviour> pBehaviour)
{
	m_pBehaviour = std::move(pBehaviour);
	m_pBehaviour->SetStartPos(m_GridCoords);
	if (auto pLevel = m_pLevelComponent.lock())
	{
		glm::vec2 pos = pLevel->GetTilePos(m_GridCoords);
		m_pTransform->SetPosition(pos.x, pos.y, 0);
	}
}

glm::ivec2 EnemyComponent::GetGridCoords() const
{
	return m_GridCoords;
}

bool EnemyComponent::GetIsharmfull() const
{
	return m_pBehaviour->GetIsHarmfull();
}
