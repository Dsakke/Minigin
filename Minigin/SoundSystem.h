#pragma once
#include "BaseSoundSystem.h"
#include <concurrent_queue.h>
#include <unordered_map>
// not sure if this the best way to foward declare this
// found example here https://stackoverflow.com/questions/19001700/how-to-forward-declare-a-class-which-is-in-a-namespace
namespace FMOD
{
	class System;
	class Sound;
}
namespace dae
{
	class SoundSystem final : public BaseSoundSystem
	{
	public:
		SoundSystem();
		~SoundSystem();
		void PlaySound(const std::string& fileName) override;
		
	private:
		void Loop();

		bool m_Continue;
		concurrency::concurrent_queue<std::string> m_SoundQueue;
		std::unordered_map<std::string, FMOD::Sound*> m_Sounds; // Don't want to place these sounds in the resource manager because it's FMOD specific
		std::thread m_Thread;
		FMOD::System* m_pSystem;
	};
}