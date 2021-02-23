#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <iostream>
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for (InputAction& action : m_KeyDownActions)
	{
		delete action.pCommand;
	}
	for (InputAction& action : m_KeyPressedActions)
	{
		delete action.pCommand;
	}
	for (InputAction& action : m_KeyUpActions)
	{
		delete action.pCommand;
	}
}

void dae::InputManager::ProcessInput()
{
	// todo: read the input
	m_PrevControllerState = m_ControllerState;
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
	XInputGetState((DWORD)0, &m_ControllerState);

	for (InputAction& action : m_KeyDownActions)
	{
		if (m_ControllerState.Gamepad.wButtons & static_cast<WORD>(action.controllerButton) & ~m_PrevControllerState.Gamepad.wButtons)
		{
			action.pCommand->Execute();
		}
	}
	for (InputAction& action  : m_KeyUpActions)
	{
			if (m_PrevControllerState.Gamepad.wButtons & static_cast<WORD>(action.controllerButton) & ~m_ControllerState.Gamepad.wButtons)
			{
				action.pCommand->Execute();
			}
	}
	for (InputAction& action : m_KeyPressedActions)
	{		
			if (m_ControllerState.Gamepad.wButtons & static_cast<WORD>(action.controllerButton))
			{
				action.pCommand->Execute();
			}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_KeyDownActions[0].pCommand->Execute(); // dirty temp fix, do change
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
	if (action.inputType == InputType::keyDown)
	{
		m_KeyDownActions.push_back(action);
	}
	else if (action.inputType == InputType::keyUp)
	{
		m_KeyUpActions.push_back(action);
	}
	else if (action.inputType == InputType::keyUp)
	{
		m_KeyUpActions.push_back(action);
	}
	action.pCommand = nullptr;
}
