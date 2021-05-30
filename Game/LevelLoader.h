#pragma once
#include <memory>
#include <string>

namespace dae
{
	class Scene;
	class Transform;
	class GameObject;
}
class LevelComponent;

std::shared_ptr<LevelComponent> LoadLevel(const std::string& file, dae::Scene& scene, const dae::Transform& transfrom);
