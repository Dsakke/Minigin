#include "MiniginPCH.h"
#include "SoundSystem.h"
#include <fmod.hpp>

dae::SoundSystem::SoundSystem()
	: m_Continue{true}
	, m_SoundQueue{}
{
	m_Thread = std::thread(&dae::SoundSystem::Loop, this);
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pSystem);
	if (result != FMOD_OK)
	{
		std::cout << "Failed to create FMOD::System\n";
	}
	result = m_pSystem->init(256, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		std::cout << "Failed to init FMOD::System\n";
	}
}

dae::SoundSystem::~SoundSystem()
{
	m_Continue = false;
	if (m_Thread.joinable())
	{
		m_Thread.join(); // we have to wait for the thread to finish because if we release the system before the thread is finished it might cause problems
	}
	if (m_pSystem)
	{
		m_pSystem->release();
		m_pSystem = nullptr;
	}
	for (std::pair<std::string, FMOD::Sound*> sounds : m_Sounds)
	{
		sounds.second->release();
	}
}

void dae::SoundSystem::AddSound(const std::string& fileName)
{
	m_SoundQueue.push(fileName);
}

void dae::SoundSystem::Loop()
{
	while (m_Continue)
	{
		std::string fileName{};
		if (m_SoundQueue.try_pop(fileName))
		{
			FMOD_RESULT result{};
			FMOD::Sound* pSound;
			result = m_pSystem->createSound(fileName.c_str(), FMOD_DEFAULT, nullptr, &pSound);
			if (result == FMOD_OK)
			{
				m_pSystem->playSound(pSound, nullptr, false, nullptr);
			}
			else
			{
				std::cout << ("Failed to create sound from " + fileName + '\n') ;
			}
		}
	}
}
