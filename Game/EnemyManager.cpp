#include "EnemyManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Factories.h"
#include "EnemyComponent.h"
#include <algorithm>
#include "SpriteRenderComponent.h"
#include <stdexcept>
#include "TimeManager.h"

EnemyManager::EnemyManager(int initSize, dae::Scene& scene, std::weak_ptr<LevelComponent> pLevel, float spawnTime)
	: m_Enemies{}
	, m_Scene{scene}
	, m_pLevelComponent{ pLevel }
	, m_SpawnTime{spawnTime}
	, m_SpawnTimer{0}
{
	m_Enemies.reserve(initSize);
}

void EnemyManager::Update()
{
	m_SpawnTimer += dae::Time::GetInstance()->GetElapsed();
	if (m_SpawnTimer >= m_SpawnTime)
	{
		ActivateEnemy();
		m_SpawnTimer = 0.f;
	}
}

void EnemyManager::Draw()
{
}

void EnemyManager::Initialize()
{
}

void EnemyManager::Reset()
{
	auto func = [](std::weak_ptr<EnemyComponent>& pEnemyWeak)
	{
		pEnemyWeak.lock()->GetGameObject().lock()->SetActive(false);
	};
	std::for_each(m_Enemies.begin(), m_Enemies.end(), func);
}

void EnemyManager::AddEnemy(std::unique_ptr<IEnemyBehaviour> pBehaviour, std::shared_ptr<dae::Texture2D> pTexture)
{
	std::shared_ptr<dae::GameObject> pObject = Factories::EnemyFactory(m_pLevelComponent, std::move(pBehaviour));
	pObject->SetActive(false);
	m_Scene.Add(pObject);
	std::shared_ptr<EnemyComponent> pEnemy = pObject->GetComponent<EnemyComponent>();
	std::shared_ptr<dae::SpriteRenderComponent> pSpriteRender = pObject->GetComponent<dae::SpriteRenderComponent>();
	pSpriteRender->SetTexture(pTexture);
	m_Enemies.push_back(pEnemy);
}

std::shared_ptr<EnemyComponent> EnemyManager::GetOverlapping(const glm::ivec2& pos)
{
	auto pred = [=](std::weak_ptr<EnemyComponent>& pEnemy)
	{
		return (pEnemy.lock()->GetGridCoords() == pos) && pEnemy.lock()->GetGameObject().lock()->GetIsActive();
	};
	auto it = std::find_if(m_Enemies.begin(), m_Enemies.end(), pred);
	if (it != m_Enemies.end())
	{
		return it->lock();
	}
	return std::shared_ptr<EnemyComponent>();
}

bool EnemyManager::ActivateEnemy()
{
	std::random_shuffle(m_Enemies.begin(), m_Enemies.end()); // select a random non-active enemy to activate
	auto pred = [](std::weak_ptr<EnemyComponent> pEnemy)
	{
		return !(pEnemy.lock()->GetGameObject().lock()->GetIsActive());
	};
	auto it = std::find_if(m_Enemies.begin(), m_Enemies.end(), pred);

	if (it == m_Enemies.end())
	{
		return false;
	}

	std::shared_ptr<EnemyComponent> pEnemy = it->lock();
	std::shared_ptr<dae::GameObject> pObject = pEnemy->GetGameObject().lock();
	pEnemy->Reset();
	pObject->SetActive(true);
	return true;
}
