#pragma once
#include <Windows.h>
#include <memory>
#include <string>

namespace dae
{
	class Scene;
	class Transform;
	class GameObject;
}
class LevelComponent;

std::shared_ptr<LevelComponent> LoadLevel(const std::string& file, const dae::Transform& transfrom);
