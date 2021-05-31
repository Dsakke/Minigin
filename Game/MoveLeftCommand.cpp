#include "MoveLeftCommand.h"
#include "QbertComponent.h"

MoveLeftCommand::MoveLeftCommand(std::weak_ptr<QBertComponent> pQBert)
	: m_pQBert{pQBert}
{
}

void MoveLeftCommand::Execute()
{
	if (auto pQBert = m_pQBert.lock())
	{
		pQBert->MoveLeft();
	}
}
