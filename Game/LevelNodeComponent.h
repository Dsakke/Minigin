#pragma once
#include "Component.h"
#include "Subject.h"
#include <memory>

namespace dae
{
	class SpriteRenderComponent;
	class Texture2D;	
}
class LevelNodeComponent final : public dae::Component, public dae::Subject,  public std::enable_shared_from_this<LevelNodeComponent>
{
public:
#pragma region NodeMode
	enum class NodeMode
	{
		level1 = 1,
		level2 = 2,
		level3 = 3
	};
#pragma endregion
	LevelNodeComponent(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, NodeMode mode);
	LevelNodeComponent(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureHalfActive, std::shared_ptr<dae::Texture2D> pTextureActive);
	~LevelNodeComponent() = default;
	void Update() override;
	void Draw() override;
	void Initialize() override;


	void SteppedOn();
protected:
	std::shared_ptr<dae::SpriteRenderComponent> m_pSpriteRenderer;
	std::shared_ptr<dae::Texture2D> m_pTextureNotActive;
	std::shared_ptr<dae::Texture2D> m_pTextureHalfActive;
	std::shared_ptr<dae::Texture2D> m_pTextureActive;
	NodeMode m_NodeMode;
	int m_StepCount;

	void Level1SteppedOn();
	void Level2SteppedOn();
	void Level3SteppedOn();
};