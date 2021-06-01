#pragma once
#include "Component.h"
#include <vector>
#include "glm.hpp"

namespace dae
{
	class Scene;
	class Texture2D;
	class SpriteRenderComponent;
	class TransformComponent;
}

class LifeComponent final : public dae::Component
{
public:
	LifeComponent(LifeComponent&&) = delete;
	LifeComponent(const LifeComponent&) = delete;
	LifeComponent& operator=(LifeComponent&&) = delete;
	LifeComponent& operator=(const LifeComponent&) = delete;

	LifeComponent(dae::Scene& scene, const glm::vec2& leftHeartPos, std::shared_ptr<dae::Texture2D> pEmptyHeart, std::shared_ptr<dae::Texture2D> pFullHeart, int maxLives = 3);
	void LoseLife();
	void GainLife();

	void Update() override;
	void Draw() override;
	void Initialize() override;
private:
	std::vector<std::shared_ptr<dae::SpriteRenderComponent>> m_pHearts;
	std::shared_ptr<dae::Texture2D> m_pEmptyHeart;
	std::shared_ptr<dae::Texture2D> m_pFullHeart;
	const int m_MaxLives;
	int m_Lives;

	void Died();
	std::shared_ptr<dae::TransformComponent> HeartFactory(dae::Scene& scene); // Factory in here because this should be the only place hearts are made
};