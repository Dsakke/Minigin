#pragma once
#include "Command.h"

class ExitCommand : public Command
{
public:
	ExitCommand(bool& doContinue);

	void Execute() override;
private:
	bool& m_Continue;
};

