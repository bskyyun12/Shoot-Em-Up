#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "BackgroundScroll.h"

class ScreenManager
{
private:

	enum SCREENS
	{
		start,
		play
	};

	static ScreenManager* sInstance;

	InputManager* mInputManager = nullptr;

	StartScreen* mStartScreen = nullptr;
	PlayScreen* mPlayScreen = nullptr;
	BackgroundScroll* mBackgroundScroll = nullptr;

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

