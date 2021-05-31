#pragma once
#include "Command.h"
namespace dae
{
	class ToggleDebugCommand final : public Command
	{
	public:
		void Execute() override;
	};
}