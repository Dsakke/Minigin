#include "MiniginPCH.h"
#include "GainScoreCommand.h"
#include "QBertComponent.h"

GainScoreCommand::GainScoreCommand(std::shared_ptr<QBertComponent> pQBertComponent)
	: m_pQBertComponent{pQBertComponent}
{
}

void GainScoreCommand::Execute()
{
	m_pQBertComponent->GainScore();
}
