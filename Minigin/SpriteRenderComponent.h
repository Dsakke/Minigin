#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class Texture2D;
	class SpriteRenderComponent : public Component
	{
	public:
		SpriteRenderComponent();
		SpriteRenderComponent(std::shared_ptr<Texture2D> pTexture);
		~SpriteRenderComponent() = default;

		void Update() override;
		void Draw() override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}