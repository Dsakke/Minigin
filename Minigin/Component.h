#pragma once
#include <memory>
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Initialize() = 0;

		void RootUpdate();
		void RootInitialize();

		void SetOwner(std::weak_ptr<GameObject> pOwner);
		std::weak_ptr<GameObject> GetGameObject();
		const std::weak_ptr<GameObject> GetGameObject() const;
	protected:
		std::weak_ptr<GameObject> m_pOwner;
		bool m_IsInitialized;

};
}