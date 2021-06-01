#pragma once
#include "Component.h"
#include "Subject.h"
namespace dae
{
	class TransformComponent;
}
class LevelComponent;
class LifeComponent;

class QBertComponent final : public dae::Component, public dae::Subject
{
public:
	QBertComponent(QBertComponent&&) = delete;
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent& operator=(QBertComponent&&) = delete;
	QBertComponent& operator=(const QBertComponent&) = delete;

	QBertComponent(std::weak_ptr<LevelComponent> pLevel);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Update() override;
	void Draw() override;
private:
	std::weak_ptr<dae::TransformComponent> m_pTransform;
	std::weak_ptr<LevelComponent> m_pLevelComponent;
	std::weak_ptr<LifeComponent> m_pLifeComponent;
	int m_GridX;
	int m_GridY;


	void FellOffGrid();
	void MoveToNewPos();
};