#pragma once
#include <memory>
#include <string>
#include  "LevelNodeComponent.h"

namespace dae
{
	class GameObject;
	class Texture2D;
}
namespace Factories
{
	
	std::shared_ptr<dae::GameObject> LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, LevelNodeComponent::NodeMode mode);
	std::shared_ptr<dae::GameObject> LevelNodeFactory(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, std::shared_ptr<dae::Texture2D> pTextureHalfActive);

}