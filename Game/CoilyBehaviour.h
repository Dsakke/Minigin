#pragma once
#include "IEnemyBehaviour.h"
#include "glm.hpp"

namespace dae
{
	class Texture2D;
}

class QBertComponent;
class CoilyBehaviour final : public IEnemyBehaviour
{
public:
	CoilyBehaviour(std::weak_ptr<QBertComponent> pQBert, std::shared_ptr<dae::Texture2D> pEggTexture, std::shared_ptr<dae::Texture2D> pCoilyTexture);
	bool operator()(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) const;
	void SetStartPos(glm::ivec2& gridCoords, std::weak_ptr<LevelComponent> pLevel) override;
	bool GetIsHarmfull() const override;
private:
	std::weak_ptr<QBertComponent> m_pQBert;
	std::shared_ptr<dae::Texture2D> m_pEggTexture;
	std::shared_ptr<dae::Texture2D> m_pCoilyTexture;
	bool m_Hatched;
};