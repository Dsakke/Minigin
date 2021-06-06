#include "UggBehaviour.h"
#include "LevelComponent.h"

UggBehaviour::UggBehaviour(bool goingRight)
	: IEnemyBehaviour{}
	, m_GoingRight{ goingRight }
{
}

bool UggBehaviour::operator()(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) const
{
	--gridCoords.y;
	if (!m_GoingRight)
	{
		--gridCoords.x;
	}
	if (auto pLevelShared = pLevel.lock())
	{
		return pLevelShared->FallsOfLevel(gridCoords);
	}
	return false;
}

void UggBehaviour::SetStartPos(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel)
{
	if (auto pLevelShared = pLevel.lock())
	{
		Level& level = pLevelShared->GetLevel();
		size_t lastRow = level.size() - 1;
		gridCoords.y = static_cast<int>(lastRow);
		if (m_GoingRight)
		{
			gridCoords.x = 0;
		}
		else
		{
			gridCoords.x = static_cast<int>(level[lastRow].size() - 1);
		}
	}
}

bool UggBehaviour::GetIsHarmfull() const
{
	return true;
}
