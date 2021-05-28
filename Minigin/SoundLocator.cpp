#include "MiniginPCH.h"
#include "SoundLocator.h"
#include "NullSoundSystem.h"

namespace dae
{
    std::shared_ptr<BaseSoundSystem> SoundLocator::m_pSoundSystem{};
    std::shared_ptr<NullSoundSystem> SoundLocator::m_pNullSoundSystem{std::make_shared<NullSoundSystem>()};

    std::shared_ptr<BaseSoundSystem> SoundLocator::GetSoundSystem()
    {
        if (m_pSoundSystem)
        {
            return m_pSoundSystem;
        }
        return m_pNullSoundSystem;
    }

    void SoundLocator::ProvideSoundSystem(std::shared_ptr<BaseSoundSystem> pSoundSystem)
    {
        m_pSoundSystem = pSoundSystem;
    }
}