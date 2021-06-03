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
class ScoreComponent;
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

	bool FallsOfLevel(const glm::ivec2& coords) const;
	void StepOnTile(const glm::ivec2& coords);
	glm::vec2 GetTilePos(const glm::ivec2& coords) const;
	Level& GetLevel();
	int GetNodeSize() const;

	void AddScoreObserver(std::weak_ptr<ScoreComponent> pScore);

private:
	void LevelWon();

	Level m_Level;
	int m_TotalNodes;
	int m_ActiveNodes;
	int m_NodeSize;
};