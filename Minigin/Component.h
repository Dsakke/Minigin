#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Update() = 0;
		virtual void Draw() = 0;

		void SetOwner(std::weak_ptr<GameObject> pOwner);
	protected:
		std::weak_ptr<GameObject> m_pOwner;

};
}