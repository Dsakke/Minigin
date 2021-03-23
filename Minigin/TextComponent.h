#pragma once
#include "Component.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace dae
{
	class Font;	
	class Texture2D;
	class TextComponent final : public Component
	{
	public:
		TextComponent(std::shared_ptr<Font> font);
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() = default;
		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

		void SetText(const std::string& text);

		void Update() override;
		void Draw() override;


	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
