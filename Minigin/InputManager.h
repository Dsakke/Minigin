#pragma once
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")
#include <vector>
#include "Singleton.h"


class Command;
namespace dae
{
	// We Give the enum specific values so we can later bitwise and them with the GamePad
	// Values are taken from https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
	enum class ControllerButton : WORD
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	enum class InputType
	{
		keyDown,
		keyUp,
		KeyPressed
	};

	struct InputAction
	{
		Command* pCommand;
		InputType inputType;
		ControllerButton controllerButton;
		int keyboardCode;
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();

		void ProcessInput();
		bool IsPressed(ControllerButton button) const;

		void AddAction(InputAction&& action); // we want to leave the given action in an invalid state as to not delete the command twice


	private:
		std::vector<InputAction> m_KeyDownActions;
		std::vector<InputAction> m_KeyPressedActions;
		std::vector<InputAction> m_KeyUpActions;

		XINPUT_STATE m_ControllerState;
		XINPUT_STATE m_PrevControllerState;

		InputManager() = default;

		friend class Singleton<InputManager>;

	};
}