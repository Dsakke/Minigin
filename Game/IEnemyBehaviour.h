#pragma once
#include <memory>
#include "glm.hpp"

class LevelComponent;
class IEnemyBehaviour
{
public:
	IEnemyBehaviour() = default;
	virtual ~IEnemyBehaviour() = default;

	IEnemyBehaviour(const IEnemyBehaviour&) = delete;
	IEnemyBehaviour(IEnemyBehaviour&&) = delete;
	IEnemyBehaviour& operator=(const IEnemyBehaviour&) = delete;
	IEnemyBehaviour& operator=(IEnemyBehaviour&&) = delete;

	virtual void operator()(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) const = 0;
	virtual void SetStartPos(glm::ivec2& gridCoords) = 0;
	virtual bool GetIsHarmfull() const = 0;
private:
};