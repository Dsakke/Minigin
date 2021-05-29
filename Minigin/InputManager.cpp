#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <iostream>
#include <SDL.h>

dae::InputManager::InputManager()
	: m_KeyDownActions{}
	, m_KeyUpActions{}
	, m_KeyPressedActions{}
	, m_ControllerState{}
	, m_PrevControllerState{}
{

}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput()
{
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
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) // this is a specific case because we alsways want to be able to close the game
		{ 
			return false;
		}
		else if (e.type == SDL_KEYDOWN) 
		{
			for (InputAction& action : m_KeyDownActions)
			{
				if (e.key.keysym.scancode == action.GetKeyboardCode())
				{
					action.GetCommand()->Execute();
				}
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			for (InputAction& action : m_KeyDownActions)
			{
				if (e.key.keysym.scancode == action.GetKeyboardCode())
				{
					action.GetCommand()->Execute();
				}
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			for (InputAction& action : m_KeyUpActions)
			{
				if (e.key.keysym.scancode == action.GetKeyboardCode())
				{
					action.GetCommand()->Execute();
				}
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			for (InputAction& action : m_KeyUpActions)
			{
				if (e.key.keysym.scancode == action.GetKeyboardCode())
				{
					action.GetCommand()->Execute();
				}
			}
		}
	}
	return true;
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

dae::InputAction::InputAction(std::shared_ptr<Command> pCommand, InputType inputType, ControllerButton controllerButton, SDL_Scancode keyBoardCode)
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

inline SDL_Scancode dae::InputAction::GetKeyboardCode() const
{
	return m_KeyboardCode;
}
