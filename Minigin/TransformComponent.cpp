#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace dae
{
	TransformComponent::TransformComponent()
		: Component{}
		, m_Transform{}
	{
		m_Transform.SetPosition(0, 0, 0);
	}

	TransformComponent::TransformComponent(float x, float y, float z)
		: Component{}
		, m_Transform{}
	{
		m_Transform.SetPosition(x, y, z);
	}

	void TransformComponent::Update()
	{
	}

	void TransformComponent::Draw() 
	{
	}

	void TransformComponent::Initialize()
	{
	}

	const Transform& TransformComponent::GetTransform() const
	{
		return m_Transform;
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		m_Transform.SetPosition(x, y, z);
	}
}
