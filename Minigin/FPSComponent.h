#pragma once
#include "Component.h"
namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;

		void Update() override;
		void Draw() override;
		void Initialize() override;
	private:

	};
}