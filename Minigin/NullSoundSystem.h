#pragma once
#include "BaseSoundSystem.h"
namespace dae
{
	class NullSoundSystem final : public BaseSoundSystem
	{
	public:
		void AddSound(const std::string& fileName) override;
	};
}