#pragma once
#include "Command.h"

class ToggleDebugCommand final : public Command
{
public:
	void Execute() override;
};