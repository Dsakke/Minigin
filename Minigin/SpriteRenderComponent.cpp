#include "MiniginPCH.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Texture2D.h"


dae::SpriteRenderComponent::SpriteRenderComponent()
	: m_pTexture{}
{
}

dae::SpriteRenderComponent::SpriteRenderComponent(std::shared_ptr<Texture2D> pTexture)
	: m_pTexture{pTexture}
{
}



void dae::SpriteRenderComponent::Update()
{
}

void dae::SpriteRenderComponent::Draw()
{
	if (auto pOwner = m_pOwner.lock())
	{
		const auto pTransComponent = pOwner->GetComponent<TransformComponent>();
		if (!pTransComponent)
		{
			throw std::runtime_error(std::string("SpriteRenderComponent was attached to GameObject without a TransformComponent"));
		}
		const auto pos = pTransComponent->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}
