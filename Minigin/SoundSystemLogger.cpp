#include "MiniginPCH.h"
#include "SoundSystemLogger.h"
#include <iostream>

dae::SoundSystemLogger::SoundSystemLogger(std::shared_ptr<BaseSoundSystem> pSoundSystem)
	: m_pSoundSystem{pSoundSystem}
{
}

dae::SoundSystemLogger::~SoundSystemLogger()
{
}

void dae::SoundSystemLogger::PlaySound(const std::string& fileName)
{
	m_pSoundSystem->PlaySound(fileName);
	std::cout << fileName << " Sound played\n";
}
