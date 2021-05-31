#include "MiniginPCH.h"
#include "ExitCommand.h"
namespace dae
{
	ExitCommand::ExitCommand(bool& doContinue)
		: m_Continue{ doContinue }
	{
	}

	void ExitCommand::Execute()
	{
		m_Continue = false;
	}
}
