#include "Factories.h"
#include "SpriteRenderComponent.h"
#include "LevelNodeComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"


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
