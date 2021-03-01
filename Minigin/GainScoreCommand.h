#pragma once
#include "Command.h"
#include <memory>
class QBertComponent;
class GainScoreCommand final : public Command
{
public:
	GainScoreCommand(std::shared_ptr<QBertComponent> pQBertComponent);

	void Execute() override;
private:
	std::shared_ptr<QBertComponent> m_pQBertComponent;
};