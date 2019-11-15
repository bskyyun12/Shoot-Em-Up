#ifndef _INPTMANAGER_H
#define _INPTMANAGER_H

#include <SDL.h>
#include "MathHelper.h"
#include <vector>

using std::vector;
using std::pair;

class InputManager {

public:
	
	enum MOUSE_BUTTON { left = 0, right, middle, back, forward };

private:

	static InputManager* sInstance;

	Uint8* mPrevKeyboardState;
	const Uint8* mKeyboardState;
	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;

	int mMouseXPos;
	int mMouseYPos;

public:

	static InputManager* Instance();

	static void Release();


	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTON botton);
	bool MouseButtonPressed(MOUSE_BUTTON button);
	bool MouseButtonReleased(MOUSE_BUTTON button);

	Vector2D MousePos();

	//----------------------------------------------------------------------------------
	//Updates the Input States (should be called once per frame before any input check) 
	//----------------------------------------------------------------------------------
	void Update();
	//-------------------------------------------------------------------------------------------------
	//Sets the current frame's key states as the previous key states (to be called in the LateUpdate)  
	//No input checks should be made in the current frame after this function is called                
	//-------------------------------------------------------------------------------------------------
	void UpdatePrevInput();

#pragma region Gamepad Input

	void InitialiseJoysticks();
	bool JoysticksInitialiased()
	{
		return m_bJoysticksInitialised;
	}

	int xValue(int joy, int stick);
	int yValue(int joy, int stick);

	bool GetButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	void CleanJoysticks();

	// Handle joysticks events
	void OnJoystickAxisMove(SDL_Event& event);
	void OnJoystickButtonDown(SDL_Event& event);
	void OnJoystickButtonUp(SDL_Event& event);

	const int m_joystickDeadZone = 10000;

#pragma endregion

private:
	
	InputManager();
	~InputManager();

	// Gamepad Input
	vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;
	vector<pair<Vector2D*, Vector2D*>> m_joystickValues;
	vector<vector<bool>> m_buttonStates;

};

#endif

