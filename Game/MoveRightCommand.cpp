#include "MoveRightCommand.h"
#include "QbertComponent.h"

MoveRightCommand::MoveRightCommand(std::weak_ptr<QBertComponent> pQBert)
	: m_pQBert{pQBert}
{
}

void MoveRightCommand::Execute()
{
	if (auto pQBert = m_pQBert.lock())
	{
		pQBert->MoveRight();
	}
}
