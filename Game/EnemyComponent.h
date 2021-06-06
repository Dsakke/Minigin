#pragma once
#include "Component.h"
#include "glm.hpp"
#include "IEnemyBehaviour.h"

namespace dae
{
	class TransformComponent;
	class Texture2D;
	class SpriteRenderComponent;
}
class LevelComponent;
class IEnemyBehaviour;
class EnemyComponent final : public dae::Component
{
public:
	EnemyComponent(std::weak_ptr<LevelComponent> pLevelComponent, std::unique_ptr<IEnemyBehaviour>&& pBehaviour, float moveTime = 1.f);
	~EnemyComponent(); // with forward declared types used in smart pointers there needs to be a destructor in the .cpp

	void Update() override;
	void Draw() override;
	void Initialize() override;

	void Move();
	void Reset();

	void SetState(std::unique_ptr<IEnemyBehaviour> pBehaviour);
private:
	glm::ivec2 m_GridCoords;

	std::unique_ptr<IEnemyBehaviour> m_pBehaviour;
	std::shared_ptr<dae::SpriteRenderComponent> m_pSpriteRenderer;
	std::shared_ptr<dae::TransformComponent> m_pTransform;
	std::weak_ptr<LevelComponent> m_pLevelComponent;

	const float m_MoveTime;
	float m_Timer;

};