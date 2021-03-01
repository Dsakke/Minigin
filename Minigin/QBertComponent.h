#pragma once
#include "Component.h"
#include "Subject.h"


class QBertComponent : public dae::Component, public dae::Subject // just temp for the observer assignement
{
public:
	QBertComponent();

	void Die();
	void Update() override;
	void Draw() override;

	int GetLives() const;
private:
	int m_Lives;
};