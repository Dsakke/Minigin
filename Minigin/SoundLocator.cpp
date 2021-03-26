#include "MiniginPCH.h"
#include "SoundLocator.h"

namespace dae
{
    std::shared_ptr<BaseSoundSystem> SoundLocator::m_pSoundSystem{};

    std::shared_ptr<BaseSoundSystem> SoundLocator::GetSoundSystem()
    {
        return m_pSoundSystem;
    }

    void SoundLocator::ProvideSoundSystem(std::shared_ptr<BaseSoundSystem> pSoundSystem)
    {
        m_pSoundSystem = pSoundSystem;
    }
}