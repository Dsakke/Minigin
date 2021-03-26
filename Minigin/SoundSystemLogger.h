#pragma once
#include "BaseSoundSystem.h"

namespace dae
{
	class SoundSystemLogger final : public BaseSoundSystem
	{
	public:
		SoundSystemLogger(std::shared_ptr<BaseSoundSystem> pSoundSystem);
		~SoundSystemLogger();
		void AddSound(const std::string& fileName) override;
	private:
		std::shared_ptr<BaseSoundSystem> m_pSoundSystem;

	};
}