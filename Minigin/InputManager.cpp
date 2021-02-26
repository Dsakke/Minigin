#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <iostream>
#include <SDL.h>


dae::InputManager::~InputManager()
{
}

void dae::InputManager::ProcessInput()
{
	// todo: read the input
	m_PrevControllerState = m_ControllerState;
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
	XInputGetState((DWORD)0, &m_ControllerState);

	for (InputAction& action : m_KeyDownActions)
	{
		if (m_ControllerState.Gamepad.wButtons & static_cast<WORD>(action.GetControllerButton()) & ~m_PrevControllerState.Gamepad.wButtons)
		{
			action.GetCommand()->Execute();
		}
	}
	for (InputAction& action  : m_KeyUpActions)
	{
		if (m_PrevControllerState.Gamepad.wButtons & static_cast<WORD>(action.GetControllerButton()) & ~m_ControllerState.Gamepad.wButtons)
		{
			action.GetCommand()->Execute();
		}
	}
	for (InputAction& action : m_KeyPressedActions)
	{		
		if (m_ControllerState.Gamepad.wButtons & static_cast<WORD>(action.GetControllerButton()))
		{
			action.GetCommand()->Execute();
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_KeyDownActions[0].GetCommand()->Execute(); // dirty temp fix, do change
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// todo: return whether the given button is pressed or not.

	if (static_cast<WORD>(button) & m_ControllerState.Gamepad.wButtons)
	{
		return true;
	}
	return false;
}

void dae::InputManager::AddAction(InputAction&& action)
{
	if (action.GetType() == InputType::keyDown)
	{
		m_KeyDownActions.push_back(action);
	}
	else if (action.GetType() == InputType::keyUp)
	{
		m_KeyUpActions.push_back(action);
	}
	else if (action.GetType() == InputType::keyUp)
	{
		m_KeyUpActions.push_back(action);
	}
}

dae::InputAction::InputAction(std::shared_ptr<Command> pCommand, InputType inputType, ControllerButton controllerButton, int keyBoardCode)
	: m_pCommand{pCommand}
	, m_InputType{inputType}
	, m_ControllerButton{controllerButton}
	, m_KeyboardCode{ keyBoardCode }
{

}



inline std::shared_ptr<Command> dae::InputAction::GetCommand()
{
	return m_pCommand;
}

inline dae::InputType dae::InputAction::GetType() const
{
	return m_InputType;
}

inline dae::ControllerButton dae::InputAction::GetControllerButton() const
{
	return m_ControllerButton;
}

inline int dae::InputAction::GetKeyboardCode() const
{
	return m_KeyboardCode;
}
