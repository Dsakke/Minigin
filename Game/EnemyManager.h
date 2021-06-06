#pragma once
#include "Component.h"
#include <vector>

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

	void AddEnemy(std::unique_ptr<IEnemyBehaviour> pBehaviour, std::shared_ptr<dae::Texture2D> pTexture);
private:
	bool ActivateEnemy();

	std::vector<std::weak_ptr<EnemyComponent>> m_Enemies;
	dae::Scene& m_Scene;
	std::weak_ptr<LevelComponent> m_pLevelComponent;
	const float m_SpawnTime;
	float m_SpawnTimer;
};