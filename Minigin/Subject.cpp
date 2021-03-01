#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>
#include "Observer.h"


void dae::Subject::AddObserver(std::shared_ptr<dae::Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	auto it{ std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver) };
	m_pObservers.erase(it, m_pObservers.end());
}

void dae::Subject::Notify(const std::shared_ptr<GameObject> pGameObject, Events event)
{
	for (std::shared_ptr<Observer>& pObserver : m_pObservers)
	{
		pObserver->OnNotify(pGameObject, event);
	}
}
