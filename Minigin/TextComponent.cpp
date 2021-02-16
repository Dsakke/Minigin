#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{

	TextComponent::TextComponent(std::shared_ptr<Font> font)
		: m_NeedsUpdate{true}
		, m_Text{}
		, m_pFont{font}
	{
	}

	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
		: m_NeedsUpdate{true}
		, m_Text{text}
		, m_pFont{font}
	{
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	void TextComponent::Update()
	{
		if (m_NeedsUpdate)
		{
			const SDL_Color color = { 255,255, 255 };
			const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);

			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_pTexture = std::make_shared<Texture2D>(texture);
			m_NeedsUpdate = false;
		}
	}

	void TextComponent::Draw()
	{
		if (m_pTexture != nullptr)
		{
			const TransformComponent* pTransCom = m_pOwner->GetComponent<TransformComponent>();
			if (!pTransCom)
			{
				throw std::runtime_error(std::string("TextComponent is attached to GameObject without TransformComponent"));
			}
			const auto pos = pTransCom->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}

}
