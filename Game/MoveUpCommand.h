#pragma once
#include "Command.h"
#include <memory>

class QBertComponent;
class MoveUpCommand final : public dae::Command
{
public:
	MoveUpCommand(MoveUpCommand&&) = delete;
	MoveUpCommand(const MoveUpCommand&) = delete;
	MoveUpCommand& operator=(MoveUpCommand&&) = delete;
	MoveUpCommand& operator=(const MoveUpCommand&) = delete;

	MoveUpCommand(std::weak_ptr<QBertComponent> pQBert);

	void Execute() override;

private:
	std::weak_ptr<QBertComponent> m_pQBert; // weak ptr because this command shouldn't extend the lifetime of qbert
};
