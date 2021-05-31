#pragma once
#include "Component.h"

namespace dae
{
	class TransformComponent;
}
class LevelComponent;

class QBertComponent final : public dae::Component
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
	int m_GridX;
	int m_GridY;


	void FellOffGrid();
	void MoveToNewPos();
};