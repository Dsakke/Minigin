#pragma once
#include "Command.h"
class QBertComponent;
class DiedCommand final : public Command
{
public:
	DiedCommand(std::shared_ptr<QBertComponent> pQBertComponent);

	void Execute() override;
private:
	std::shared_ptr<QBertComponent> m_pQBertComponent;
};