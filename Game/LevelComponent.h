#pragma once
#include "Component.h"
#include "Observer.h"
#include <vector>
#include "Events.h"
#include "glm.hpp"

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

	LevelComponent(Level&& level, int nodeSize);
	void OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event) override;

	void Draw() override;
	void Update() override;
	void Initialize() override;

	bool FallsOfLevel(int x, int y) const;
	void StepOnTile(int x, int y);
	glm::vec2 GetTilePos(int x, int y) const;
	Level& GetLevel();
	int GetNodeSize() const;

private:
	void LevelWon();

	Level m_Level;
	int m_TotalNodes;
	int m_ActiveNodes;
	int m_NodeSize;
};