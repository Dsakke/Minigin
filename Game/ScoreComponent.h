#pragma once
#include "Component.h"
#include "Observer.h"
#include <unordered_map>
#include "Events.h"

namespace dae
{
	class TextComponent;
}

class ScoreComponent final : public dae::Component, public dae::Observer
{
public:
	ScoreComponent();

	static void ResetScore();

	void Update() override;
	void Draw() override;
	void Initialize() override;

	void OnNotify(const std::shared_ptr<dae::GameObject> pGameObject, Events event);
private:
	static int m_Score;
	std::shared_ptr<dae::TextComponent> m_pTextComponent;
	std::unordered_map<Events, int> m_EventScoreIncrements;
};