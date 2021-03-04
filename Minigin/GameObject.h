#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>
#include "Component.h"
#include <memory>

namespace dae
{
	class Texture2D;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update();
		void Render() const;

		template <class T>
		std::shared_ptr<T> GetComponent();
		template <class T>
		const std::shared_ptr<T> GetComponent() const; // We want both const and not const version of this function so we can call it from within a const function
		void AddComponent(std::shared_ptr<Component> pComponent);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::vector<std::shared_ptr<Component>> m_Components;
	};

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent()
	{
		for (std::shared_ptr<Component> pComponent : m_Components)
		{
			if (typeid(T) == typeid(*pComponent))
			{
				return std::static_pointer_cast<T>(pComponent);
			}
		}
		return nullptr;
	}

	template<class T>
	inline const std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (const std::shared_ptr<Component> pComponent : m_Components)
		{
			if (typeid(T) == typeid(*pComponent))
			{
				return std::static_pointer_cast<const T>(pComponent);
			}
		}
		return nullptr;
	}
}
