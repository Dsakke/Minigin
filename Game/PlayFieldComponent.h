#pragma once
#include "Component.h"

class PlayFieldComponent final : public dae::Component
{
public:
	PlayFieldComponent();

	void Update() override;
	void Draw() override;
private:

};