#include "MiniginPCH.h"
#include "SoundTestCommand.h"
#include "SoundLocator.h"
#include "BaseSoundSystem.h"

void SoundTestCommand::Execute()
{
	std::shared_ptr<dae::BaseSoundSystem> pSoundSystem{ dae::SoundLocator::GetSoundSystem() };
	pSoundSystem->AddSound("../Data/Sounds/Test.wav");
}
