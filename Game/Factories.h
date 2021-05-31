#pragma once
#include <memory>
#include <string>
#include  "LevelNodeComponent.h"

namespace dae
{
	class GameObject;
	class Texture2D;
}
class LevelComponent;
namespace Factories
{
	
	std::shared_ptr<dae::GameObject> LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, LevelNodeComponent::NodeMode mode);
	std::shared_ptr<dae::GameObject> LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, std::shared_ptr<dae::Texture2D> pTextureHalfActive);
	std::shared_ptr<dae::GameObject> QBertFactory(std::weak_ptr<LevelComponent> pLevel, std::shared_ptr<dae::Texture2D> pTexture);
}