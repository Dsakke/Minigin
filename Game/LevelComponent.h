#pragma once
#include "Component.h"
#include "Observer.h"
#include <vector>
#include "Events.h"

namespace dae
{
	class GameObject;
}
class LevelNodeComponent;
typedef std::vector<std::vector<std::shared_ptr<LevelNodeComponent>>> Level;
class LevelComponent final : public dae::Component, public dae::Observer, public std::enable_shared_from_this<LevelComponent>
{
public:
	LevelComponent(LevelComponent&&) = delete;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;

	LevelComponent(Level&& level);
	void OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event) override;

	void Draw() override;
	void Update() override;

	Level& GetLevel();
private:
	void LevelWon();

	Level m_Level;
	int m_TotalNodes;
	int m_ActiveNodes;
};