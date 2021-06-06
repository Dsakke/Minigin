#pragma once
#include "IEnemyBehaviour.h"

class UggBehaviour final : public IEnemyBehaviour
{
public:
	UggBehaviour(bool goingRight);

	bool operator()(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) const;
	void SetStartPos(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) override;
	bool GetIsHarmfull() const override;
private:
	bool m_GoingRight;
};