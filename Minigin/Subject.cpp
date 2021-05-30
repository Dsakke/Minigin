#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>
#include "Observer.h"


void dae::Subject::AddObserver(std::weak_ptr<dae::Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(std::weak_ptr<Observer> pObserver)
{
	auto pred = [=](std::weak_ptr<Observer> pObs) { return pObs.lock() == pObserver.lock(); };
	auto it{ std::remove_if(m_pObservers.begin(), m_pObservers.end(), pred) };
	m_pObservers.erase(it, m_pObservers.end());
}

void dae::Subject::Notify(const std::shared_ptr<GameObject> pGameObject, Events event)
{
	for (std::weak_ptr<Observer>& pObserver : m_pObservers)
	{
		if (auto pObs = pObserver.lock())
		{
			pObs->OnNotify(pGameObject, event);
		}
	}
}
