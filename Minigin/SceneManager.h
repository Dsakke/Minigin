#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetScene(const std::string& name);
		Scene& GetCurrentScene();

		void SetCurrentScene(const std::string name);
		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_pCurrentScene;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
