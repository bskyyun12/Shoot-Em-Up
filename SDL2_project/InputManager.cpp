#include <string.h>
#include "InputManager.h"
#include <iostream>

using std::cout;
using std::endl;
using std::make_pair;

InputManager* InputManager::sInstance = nullptr;

InputManager* InputManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

InputManager::InputManager() 
{
	m_bJoysticksInitialised = false;

	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
	mPrevMouseState = mMouseState;

	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	//Setting mPrevKeyboardState to be the same length as mKeyboardState
	mPrevKeyboardState = new Uint8[mKeyLength];
	//Copying the contents of mKeyboardState into mPrevKeyboardState so that it contains data on the first frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager() 
{
	//Clearing the previous keyboard state array
	delete[] mPrevKeyboardState;
	mPrevKeyboardState = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) 
{
	return (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) 
{
	//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
	return (mPrevKeyboardState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) 
{
	//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
	return (mPrevKeyboardState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
}

Vector2D InputManager::MousePos() 
{
	return Vector2D((float)mMouseXPos, (float)mMouseYPos);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button) 
{
	//mask to be using for bit wise operations
	Uint32 mask = 0;

	switch (button) 
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask exists in the current mouse state
	return ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) 
{
	Uint32 mask = 0;

	switch (button) 
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask does not exist in the previous mouse state, but exists in the current one
	return ((mPrevMouseState & mask) == 0) && ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) 
{
	Uint32 mask = 0;

	switch (button) 
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;

	case middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask exists in the previous mouse state, but does not exist in the current one
	return ((mPrevMouseState & mask) != 0) && ((mMouseState & mask) == 0);
}

void InputManager::Update() 
{
	//Updating the mouse state to get the key states of the current frame
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);

#pragma region Gamepad Events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_JOYAXISMOTION:
			OnJoystickAxisMove(event);
			break;
		case SDL_JOYBUTTONDOWN:
			OnJoystickButtonDown(event);
			break;
		case SDL_JOYBUTTONUP:
			OnJoystickButtonUp(event);
			break;
		case SDL_JOYHATMOTION:
			OnJoystickHatMove(event);
			break;
		default:
			break;
		}
	}
#pragma endregion
}

void InputManager::UpdatePrevInput() 
{
	//Copying the keyboard state into the previous keyboard state array at the end of the frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	//Setting the previous mouse state as the current mouse state at the end of the frame
	mPrevMouseState = mMouseState;
}

#pragma region Gamepad Input

void InputManager::InitialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		for (unsigned short int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); //add our pair

				vector<bool> tempButtons;

				for (unsigned short int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				cout << SDL_GetError();
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;

		cout << "Initialised " << m_joysticks.size() << " joystick(s)" << endl;
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

int InputManager::GetJoystickDeadZone()
{
	return m_joystickDeadZone;
}

int InputManager::GetNumberOfJoysticks() 
{
	return m_joysticks.size();
}

int InputManager::xValue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->GetX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->GetX();
		}
	}
	return 0;
}

int InputManager::yValue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->GetY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->GetY();
		}
	}
	return 0;
}

void InputManager::CleanJoysticks()
{
	if (m_bJoysticksInitialised)
	{
		for (unsigned short int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputManager::OnJoystickAxisMove(SDL_Event& event)
{
	int whichOne = event.jaxis.which; // get wich controller

	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			//cout << "MoveRight" << endl;
			m_joystickValues[whichOne].first->SetX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			//cout << "MoveLeft" << endl;
			m_joystickValues[whichOne].first->SetX(-1);
		}
		else
		{
			//cout << "Stop" << endl;
			m_joystickValues[whichOne].first->SetX(0);
		}
	}

	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			//cout << "MoveDown" << endl;
			m_joystickValues[whichOne].first->SetY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			//cout << "MoveUp" << endl;
			m_joystickValues[whichOne].first->SetY(-1);
		}
		else
		{
			//cout << "Stop" << endl;
			m_joystickValues[whichOne].first->SetY(0);
		}
	}

	// right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			//cout << "MoveRight" << endl;
			m_joystickValues[whichOne].second->SetX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			//cout << "MoveLeft" << endl;
			m_joystickValues[whichOne].second->SetX(-1);
		}
		else
		{
			//cout << "Stop" << endl;
			m_joystickValues[whichOne].second->SetX(0);
		}
	}

	// right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			//cout << "MoveDown" << endl;
			m_joystickValues[whichOne].second->SetY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			//cout << "MoveUp" << endl;
			m_joystickValues[whichOne].second->SetY(-1);
		}
		else
		{
			//cout << "Stop" << endl;
			m_joystickValues[whichOne].second->SetY(0);
		}
	}
}

void InputManager::OnJoystickButtonDown(SDL_Event& event)
{
	int whichOne = event.jbutton.which; // get wich controller

	cout << "ButtonPressed" << endl;
	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputManager::OnJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jbutton.which;

	cout << "ButtonReleased" << endl;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void InputManager::OnJoystickHatMove(SDL_Event& event)
{
	int whichOne = event.jhat.which; // get wich controller

	// DPAD movement
	if (event.jhat.value == SDL_HAT_UP)
	{
		//cout << "MoveUp" << endl;
		m_joystickValues[whichOne].first->SetY(-1);
	}
	if (event.jhat.value == SDL_HAT_DOWN)
	{
		//cout << "MoveDown" << endl;
		m_joystickValues[whichOne].first->SetY(1);
	}
	if (event.jhat.value == SDL_HAT_LEFT)
	{
		//cout << "MoveLeft" << endl;
		m_joystickValues[whichOne].first->SetX(-1);
	}
	if (event.jhat.value == SDL_HAT_RIGHT)
	{
		//cout << "MoveRight" << endl;
		m_joystickValues[whichOne].first->SetX(1);
	}
	if (event.jhat.value == SDL_HAT_LEFTUP)
	{
		//cout << "MoveLeftUp" << endl;
		m_joystickValues[whichOne].first->SetX(-1);
		m_joystickValues[whichOne].first->SetY(-1);
	}
	if (event.jhat.value == SDL_HAT_RIGHTUP)
	{
		//cout << "MoveRightUp" << endl;
		m_joystickValues[whichOne].first->SetX(1);
		m_joystickValues[whichOne].first->SetY(-1);
	}
	if (event.jhat.value == SDL_HAT_RIGHTDOWN)
	{
		//cout << "MoveRightDown" << endl;
		m_joystickValues[whichOne].first->SetX(1);
		m_joystickValues[whichOne].first->SetY(1);
	}
	if (event.jhat.value == SDL_HAT_LEFTDOWN)
	{
		//cout << "MoveLeftDown" << endl;
		m_joystickValues[whichOne].first->SetX(-1);
		m_joystickValues[whichOne].first->SetY(1);
	}
	if (event.jhat.value == SDL_HAT_CENTERED)
	{
		//cout << "Stop" << endl;
		m_joystickValues[whichOne].first->SetX(0);
		m_joystickValues[whichOne].first->SetY(0);
	}
}

#pragma endregion