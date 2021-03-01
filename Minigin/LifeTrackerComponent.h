#pragma once
#include "Observer.h"
#include "Component.h"
#include "Events.h"
class LifeTrackerComponent final : public dae::Component, public dae::Observer
{
public:
	LifeTrackerComponent();

	void Update() override;
	void Draw() override;

	void OnNotify(const std::shared_ptr<dae::GameObject>, Events event) override;

private:
};