#pragma once


#include "Component.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent();
		TransformComponent(float x, float y, float z);

		void Update() override;
		void Draw() override;
		void Initialize() override;

		const Transform& GetTransform() const;
		void SetPosition(float x, float y, float z);
	private:
		Transform m_Transform;
	};

}