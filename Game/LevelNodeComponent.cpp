#include "LevelNodeComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include "SpriteRenderComponent.h"
#include "Events.h"

LevelNodeComponent::LevelNodeComponent(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureActive, NodeMode mode)
	: m_pSpriteRenderer{}
	, m_pTextureNotActive{pTextureActive}
	, m_pTextureHalfActive{}
	, m_pTextureActive{pTextureActive}
	, m_NodeMode{ mode }
	, m_StepCount{0}
{
	if(mode == NodeMode::level2)
	{
		throw std::runtime_error(std::string("LevelNodeComponent constructed in level2 with only 2 texture, use the level2 specific contstructor"));
		return;
	}
}

LevelNodeComponent::LevelNodeComponent(std::shared_ptr<dae::Texture2D> pTextureNotActive, std::shared_ptr<dae::Texture2D> pTextureHalfActive, std::shared_ptr<dae::Texture2D> pTextureActive)
	: m_pSpriteRenderer{}
	, m_pTextureNotActive{pTextureNotActive}
	, m_pTextureHalfActive{pTextureHalfActive}
	, m_pTextureActive{pTextureActive}
	, m_NodeMode{NodeMode::level2}
	, m_StepCount{0}
{
}

void LevelNodeComponent::Update()
{
}

void LevelNodeComponent::Draw()
{
}

void LevelNodeComponent::Initialize()
{
	if (!m_pSpriteRenderer)
	{
		if (auto pOwner = m_pOwner.lock())
		{
			m_pSpriteRenderer = pOwner->GetComponent<dae::SpriteRenderComponent>();
			if (!m_pSpriteRenderer)
			{
				throw std::runtime_error(std::string("LevelNodeComponent was attached to GameObject without a SpriteRenderComponent"));
				return;
			}
		}
	}
}

void LevelNodeComponent::SteppedOn()
{
	switch (m_NodeMode)
	{
	case NodeMode::level1:
		Level1SteppedOn();
		break;
	case NodeMode::level2:
		Level2SteppedOn();
		break;
	case NodeMode::level3:
		Level3SteppedOn();
		break;
	default:
		break;
	}
}

void LevelNodeComponent::Level1SteppedOn()
{
	if (m_StepCount == 0)
	{
		++m_StepCount;
		m_pSpriteRenderer->SetTexture(m_pTextureActive);
		if (auto pOwner = m_pOwner.lock())
		{
			Notify(pOwner, Events::LevelNodeActivated);
		}
	}
}

void LevelNodeComponent::Level2SteppedOn()
{
	if (m_StepCount < 2)
	{
		++m_StepCount;
		switch (m_StepCount)
		{
		case 1:
			m_pSpriteRenderer->SetTexture(m_pTextureHalfActive);
			break;
		case 2:
			m_pSpriteRenderer->SetTexture(m_pTextureActive);
			if (auto pOwner = m_pOwner.lock())
			{
				Notify(pOwner, Events::LevelNodeActivated);
			}
			break;
		default:
			break;
		}
	}
}

void LevelNodeComponent::Level3SteppedOn()
{
	if (m_StepCount == 1)
	{
		--m_StepCount;
		if (auto pOwner = m_pOwner.lock())
		{
			Notify(pOwner, Events::LevelNodeDeactivated);
		}
	}
	else
	{
		++m_StepCount;
		if (auto pOwner = m_pOwner.lock())
		{
			Notify(pOwner, Events::LevelNodeActivated);
		}
	}
}

