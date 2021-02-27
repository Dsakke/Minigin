#pragma once
#include "Command.h"

class ExitCommand final : public Command
{
public:
	ExitCommand(bool& doContinue);

	void Execute() override;
private:
	bool& m_Continue;
};

