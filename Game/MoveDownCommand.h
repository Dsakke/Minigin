#pragma once
#include "Command.h"
#include <memory>

class QBertComponent;
class MoveDownCommand final : public dae::Command
{
public:
	MoveDownCommand(MoveDownCommand&&) = delete;
	MoveDownCommand(const MoveDownCommand&) = delete;
	MoveDownCommand& operator=(MoveDownCommand&&) = delete;
	MoveDownCommand& operator=(const MoveDownCommand&) = delete;

	MoveDownCommand(std::weak_ptr<QBertComponent> pQBert);

	void Execute() override;

private:
	std::weak_ptr<QBertComponent> m_pQBert; // weak ptr because this command shouldn't extend the lifetime of qbert
};
