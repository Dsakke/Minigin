#include "MoveDownCommand.h"
#include "QbertComponent.h"

MoveDownCommand::MoveDownCommand(std::weak_ptr<QBertComponent> pQBert)
	: m_pQBert{pQBert}
{
}

void MoveDownCommand::Execute()
{
	if (auto pQBert = m_pQBert.lock())
	{
		pQBert->MoveDown();
	}
}
