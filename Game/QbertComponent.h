#pragma once
#include "Component.h"
#include "Subject.h"
#include "glm.hpp"
namespace dae
{
	class TransformComponent;
}
class LevelComponent;
class LifeComponent;
class EnemyManager;

class QBertComponent final : public dae::Component, public dae::Subject
{
public:
	QBertComponent(QBertComponent&&) = delete;
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent& operator=(QBertComponent&&) = delete;
	QBertComponent& operator=(const QBertComponent&) = delete;

	QBertComponent(std::weak_ptr<LevelComponent> pLevel, std::weak_ptr<EnemyManager> pEnemyManager);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Update() override;
	void Draw() override;
	void Initialize() override;

private:
	std::weak_ptr<dae::TransformComponent> m_pTransform;
	std::weak_ptr<LevelComponent> m_pLevelComponent;
	std::weak_ptr<LifeComponent> m_pLifeComponent;
	std::weak_ptr<EnemyManager> m_pEnemyManager;
	
	glm::ivec2 m_GridCoords;


	void FellOffGrid();
	void MoveToNewPos();
};