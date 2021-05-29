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
		void AddObserver(std::shared_ptr<Observer> pObserver);
		void RemoveObserver(std::shared_ptr<Observer> pObserver);

	protected:
		void Notify(const std::shared_ptr<GameObject> pGameObject, Events event);
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}