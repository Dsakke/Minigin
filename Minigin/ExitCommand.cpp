#include "MiniginPCH.h"
#include "ExitCommand.h"

ExitCommand::ExitCommand(bool& doContinue)
	: m_Continue{ doContinue }
{
}

void ExitCommand::Execute()
{
	m_Continue = false;
}
