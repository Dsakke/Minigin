#pragma once
#include "Observer.h"
#include "Component.h"
#include <unordered_map>
#include "Events.h"

class ScoreComponent final : public dae::Component, public dae::Observer
{
public:
	ScoreComponent();
	void OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event) override;
	void Update() override;
	void Draw() override;
	void Initialize() override;


private:
	int m_Score;
	std::unordered_map<Events, int> m_EventScoreIncrements;
};