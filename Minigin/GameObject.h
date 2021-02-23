#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		template <class T>
		T* GetComponent();
		void AddComponent(Component* pComponent);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::vector<Component*> m_Components;
	};

	template<class T>
	inline T* GameObject::GetComponent()
	{
		for (Component* pComponent : m_Components)
		{
			if (typeid(T) == typeid(*pComponent))
			{
				return static_cast<T*>(pComponent);
			}
		}
		return nullptr;
	}
}
