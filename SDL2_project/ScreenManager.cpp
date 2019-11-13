#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInputManager = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mBackgroundScroll = new BackgroundScroll();

	currentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mBackgroundScroll;
	mBackgroundScroll = nullptr;
}


void ScreenManager::Update()
{
	switch (currentScreen)
	{
	case start:
		mBackgroundScroll->Update();
		mStartScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
		{
			currentScreen = play;
			mStartScreen->ResetAnimation();
		}
		break;
	case play:
		mBackgroundScroll->Update();
		mPlayScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
		{
			currentScreen = start;
		}
		break;
	default:
		break;
	}
}

void ScreenManager::Render()
{
	switch (currentScreen)
	{
	case start:
		mBackgroundScroll->Render();
		mStartScreen->Render();
		break;
	case play:
		mBackgroundScroll->Render();
		mPlayScreen->Render();
		break;
	default:
		break;
	}
}