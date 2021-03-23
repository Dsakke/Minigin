#include "MiniginPCH.h"
#include "TimeManager.h"

dae::Time* dae::Time::m_pInstance{ nullptr };

using namespace std::chrono;

dae::Time* dae::Time::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new Time{};
    }
    return m_pInstance;
}

void dae::Time::DestroyInstance()
{
    delete m_pInstance;
    m_pInstance = nullptr;
}

void dae::Time::UpdateTime()
{
    const auto currentTime = std::chrono::high_resolution_clock::now();
    m_Elapsed = duration_cast<duration<float>>(currentTime - m_Prevtime).count();
    m_Prevtime = currentTime;
}

float dae::Time::GetElapsed()
{
    return m_Elapsed;
}

dae::Time::Time()
    : m_Prevtime{std::chrono::high_resolution_clock::now()}
    , m_Elapsed{ 0 }
{

}