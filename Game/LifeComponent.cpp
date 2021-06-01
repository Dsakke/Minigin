#include "LifeComponent.h"
#include "Texture2D.h"
#include <SDL.h>
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Scene.h"

LifeComponent::LifeComponent(dae::Scene& scene, const glm::vec2& leftHeartPos, std::shared_ptr<dae::Texture2D> pEmptyHeart, std::shared_ptr<dae::Texture2D> pFullHeart, int maxLives)
	: m_pHearts{}
	, m_pEmptyHeart{pEmptyHeart}
	, m_pFullHeart{pFullHeart}
	, m_MaxLives{maxLives}
	, m_Lives{maxLives}
{
	int w{};
	SDL_QueryTexture(pFullHeart->GetSDLTexture(), nullptr, nullptr, &w, nullptr);
	for (int i{}; i < maxLives; ++i)
	{
		std::shared_ptr<dae::TransformComponent> pTransform = HeartFactory(scene);
		pTransform->SetPosition(leftHeartPos.x + i * w, leftHeartPos.y, 0);
	}
}

void LifeComponent::LoseLife()
{
	--m_Lives;
	if (m_Lives <= 0)
	{
		Died();
		return;
	}
	m_pHearts[m_Lives]->SetTexture(m_pEmptyHeart);

}

void LifeComponent::GainLife()
{
	if(m_Lives != m_MaxLives)
	{ 
		++m_Lives;
	}
}

void LifeComponent::Update()
{
}

void LifeComponent::Draw()
{
}

void LifeComponent::Initialize()
{
}

void LifeComponent::Died()
{
}

std::shared_ptr<dae::TransformComponent> LifeComponent::HeartFactory(dae::Scene& scene)
{
	std::shared_ptr<dae::GameObject> pObject = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TransformComponent> pTransform = std::make_shared<dae::TransformComponent>();
	std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer = std::make_shared<dae::SpriteRenderComponent>(m_pFullHeart);

	pObject->AddComponent(pTransform);
	pObject->AddComponent(pSpriteRenderer);
	scene.Add(pObject);
	m_pHearts.push_back(pSpriteRenderer);
	return pTransform;
}
