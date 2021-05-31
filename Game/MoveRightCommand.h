#pragma once
#include "Command.h"
#include <memory>

class QBertComponent;
class MoveRightCommand final : public dae::Command
{
public:
	MoveRightCommand(MoveRightCommand&&) = delete;
	MoveRightCommand(const MoveRightCommand&) = delete;
	MoveRightCommand& operator=(MoveRightCommand&&) = delete;
	MoveRightCommand& operator=(const MoveRightCommand&) = delete;

	MoveRightCommand(std::weak_ptr<QBertComponent> pQBert);

	void Execute() override;

private:
	std::weak_ptr<QBertComponent> m_pQBert; // weak ptr because this command shouldn't extend the lifetime of qbert
};
