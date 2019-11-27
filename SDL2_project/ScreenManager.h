#pragma once
#include "BackgroundScroll.h"
#include "StartScreen.h"
#include "PlayScreen.h"
#include "EndingScreen.h"

class ScreenManager
{
private:

	enum SCREENS
	{
		start,
		play,
		ending
	};

	static ScreenManager* sInstance;

	InputManager* mInputManager = nullptr;

	StartScreen* mStartScreen = nullptr;
	PlayScreen* mPlayScreen = nullptr;
	EndingScreen* mEndingScreen = nullptr;
	

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

