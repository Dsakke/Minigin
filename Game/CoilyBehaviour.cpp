#include "CoilyBehaviour.h"
#include "Texture2D.h"

CoilyBehaviour::CoilyBehaviour(std::weak_ptr<QBertComponent> pQBert, std::shared_ptr<dae::Texture2D> pEggTexture, std::shared_ptr<dae::Texture2D> pCoilyTexture)
	: m_pQBert{pQBert}
	, m_pEggTexture{pEggTexture}
	, m_pCoilyTexture{pCoilyTexture}
	, m_Hatched{false}
{
}



void CoilyBehaviour::operator()(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) const
{
	if (m_Hatched)
	{
		return;
	}
	else
	{
		int randInt = std::rand() % 2;
		switch (randInt)
		{
		case 0:
			++gridCoords.x;
			++gridCoords.y;
			break;
		case 1:
			++gridCoords.y;
			break;
		default:
			break;
		}
	}
}

void CoilyBehaviour::SetStartPos(glm::ivec2& gridCoords)
{
	gridCoords.x = rand() % 2;
	gridCoords.y = 1;
}

bool CoilyBehaviour::GetIsHarmfull() const
{
	return true;
}
