#include "Factories.h"
#include "SpriteRenderComponent.h"
#include "LevelNodeComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "QbertComponent.h"
#include "LevelComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

std::shared_ptr<dae::GameObject> Factories::ScoreFactory(std::shared_ptr<dae::Font> pFont)
{
	std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextComponent> pText = std::make_shared<dae::TextComponent>(pFont);
	std::shared_ptr<ScoreComponent> pScore = std::make_shared<ScoreComponent>();
	std::shared_ptr<dae::TransformComponent> pTransform = std::make_shared<dae::TransformComponent>();

	pObject->AddComponent(pText);
	pObject->AddComponent(pScore);
	pObject->AddComponent(pTransform);
	return pObject;
}

std::shared_ptr<dae::GameObject> Factories::LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, LevelNodeComponent::NodeMode mode)
{
	std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();

	std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer = std::make_shared<dae::SpriteRenderComponent>(pTextureNotActive);
	pObject->AddComponent(pSpriteRenderer);

	std::shared_ptr<LevelNodeComponent> pLevelNodeComponent = std::make_shared<LevelNodeComponent>(pTextureNotActive, pTextureActive, mode);
	pObject->AddComponent(pLevelNodeComponent);

	std::shared_ptr<dae::TransformComponent> pTransform = std::make_shared<dae::TransformComponent>(0.f, 0.f, 0.f);
	pObject->AddComponent(pTransform);

	return pObject;
}

std::shared_ptr<dae::GameObject> Factories::LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, std::shared_ptr<dae::Texture2D> pTextureHalfActive)
{
	std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();

	std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer = std::make_shared<dae::SpriteRenderComponent>(pTextureNotActive);
	pObject->AddComponent(pSpriteRenderer);

	std::shared_ptr<LevelNodeComponent> pLevelNodeComponent = std::make_shared<LevelNodeComponent>(pTextureNotActive, pTextureHalfActive, pTextureActive);
	pObject->AddComponent(pLevelNodeComponent);

	std::shared_ptr<dae::TransformComponent> pTransform = std::make_shared<dae::TransformComponent>(0.f, 0.f, 0.f);
	pObject->AddComponent(pTransform);

	return pObject;
}

std::shared_ptr<dae::GameObject> Factories::QBertFactory(std::weak_ptr<LevelComponent> pLevel, std::shared_ptr<dae::Texture2D> pTexture)
{
	std::shared_ptr<LevelComponent> pLevelShared = pLevel.lock();

	glm::vec2 initPos = pLevelShared->GetTilePos(0, 0); // (0,0) is the top of the pyramid
	std::shared_ptr<dae::TransformComponent> pTransform = std::make_shared<dae::TransformComponent>(initPos.x, initPos.y, 0.f);

	std::shared_ptr<QBertComponent> pQBert = std::make_shared<QBertComponent>(pLevel);

	std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer = std::make_shared<dae::SpriteRenderComponent>(pTexture);

	std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();

	pObject->AddComponent(pTransform);
	pObject->AddComponent(pQBert);
	pObject->AddComponent(pSpriteRenderer);

	return pObject;
}
