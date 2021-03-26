#pragma once

namespace dae
{
	class BaseSoundSystem;
	class SoundLocator final
	{
	public:
		SoundLocator() = delete;
		~SoundLocator() = delete;

		static std::shared_ptr<BaseSoundSystem> GetSoundSystem();
		static void ProvideSoundSystem(std::shared_ptr<BaseSoundSystem> pSoundSystem);
	private:
		static std::shared_ptr<BaseSoundSystem> m_pSoundSystem;

	};
}