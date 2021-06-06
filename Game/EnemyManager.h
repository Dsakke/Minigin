#pragma once
#include "Component.h"
#include <vector>
#include "glm.hpp"

namespace dae
{
	class Scene;
	class Texture2D;
}
class EnemyComponent;
class LevelComponent;
class IEnemyBehaviour;
class EnemyManager : public dae::Component
{
public:
	EnemyManager(int initSize, dae::Scene& scene, std::weak_ptr<LevelComponent> pLevel, float spawnTime);

	void Update() override;
	void Draw() override;
	void Initialize() override;

	void Reset();
	void AddEnemy(std::unique_ptr<IEnemyBehaviour> pBehaviour, std::shared_ptr<dae::Texture2D> pTexture);
	std::shared_ptr<EnemyComponent> GetOverlapping(const glm::ivec2& pos);
private:
	bool ActivateEnemy();

	std::vector<std::weak_ptr<EnemyComponent>> m_Enemies;
	dae::Scene& m_Scene;
	std::weak_ptr<LevelComponent> m_pLevelComponent;
	const float m_SpawnTime;
	float m_SpawnTimer;
};