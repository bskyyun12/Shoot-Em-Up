#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "EndingScreen.h"
#include "KeyOptionScreen.h"
#include "InputManager.h"

class ScreenManager
{
private:

	enum SCREENS
	{
		start,
		play,
		ending,
		keyOption
	};

	static ScreenManager* sInstance;

	InputManager* mInputManager = nullptr;

	StartScreen* mStartScreen = nullptr;
	PlayScreen* mPlayScreen = nullptr;
	EndingScreen* mEndingScreen = nullptr;
	KeyOptionScreen* mKeyOptionScreen = nullptr;
	

	SCREENS currentScreen;

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	ScreenManager();
	~ScreenManager();

};

