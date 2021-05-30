#pragma once
#include <vector>
#include <memory>
#include "Events.h"

namespace dae
{
	class Observer;
	class GameObject;
	class Subject
	{
	public:
		virtual ~Subject() = default;

		void AddObserver(std::weak_ptr<Observer> pObserver);
		void RemoveObserver(std::weak_ptr<Observer> pObserver);

	protected:
		void Notify(const std::shared_ptr<GameObject> pGameObject, Events event);
	private:
		std::vector<std::weak_ptr<Observer>> m_pObservers;
	};
}