#pragma once
#include "BaseSoundSystem.h"
namespace dae
{
	class NullSoundSystem final : public BaseSoundSystem
	{
	public:
		void PlaySound(const std::string& fileName) override;
	};
}