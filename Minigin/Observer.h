#pragma once
#include "Events.h"

namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const std::shared_ptr<GameObject> pGameObject, Events event) = 0;
	private:
	};
}