#include "MoveUpCommand.h"
#include "QbertComponent.h"

MoveUpCommand::MoveUpCommand(std::weak_ptr<QBertComponent> pQBert)
	: m_pQBert{pQBert}
{
}

void MoveUpCommand::Execute()
{
	if (auto pQBert = m_pQBert.lock())
	{
		pQBert->MoveUp();
	}
}
