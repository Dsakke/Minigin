#pragma once
#include "SceneManager.h"

namespace dae
{
	class InputManager;
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		InputManager& GetInputManager();
		const std::string& GetName() const;
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::shared_ptr<dae::InputManager> m_pInputManager;
		static unsigned int m_IdCounter; 
	};

}
