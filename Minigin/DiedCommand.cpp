#include "MiniginPCH.h"
#include "DiedCommand.h"
#include "QBertComponent.h"

DiedCommand::DiedCommand(std::shared_ptr<QBertComponent> pQBertComponent)
	: m_pQBertComponent{ pQBertComponent }
{
}

void DiedCommand::Execute()
{
	m_pQBertComponent->Die();
}
