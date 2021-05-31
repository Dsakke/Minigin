#include "Command.h"
#include <memory>

class QBertComponent;
class MoveLeftCommand final : public dae::Command
{
public:
	MoveLeftCommand(MoveLeftCommand&&) = delete;
	MoveLeftCommand(const MoveLeftCommand&) = delete;
	MoveLeftCommand& operator=(MoveLeftCommand&&) = delete;
	MoveLeftCommand& operator=(const MoveLeftCommand&) = delete;

	MoveLeftCommand(std::weak_ptr<QBertComponent> pQBert);

	void Execute() override;

private:
	std::weak_ptr<QBertComponent> m_pQBert; // weak ptr because this command shouldn't extend the lifetime of qbert
};