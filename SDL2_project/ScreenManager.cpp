#include "ScreenManager.h"
#include "InputManager.h"

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

	currentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}


void ScreenManager::Update()
{
#pragma region Gamepad Events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_JOYBUTTONDOWN:
			mInputManager->OnJoystickButtonDown(event);
			break;
		case SDL_JOYBUTTONUP:
			mInputManager->OnJoystickButtonUp(event);
			break;
		default:
			break;
		}
	}
#pragma endregion
	switch (currentScreen)
	{
	case start:
		mStartScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN) || (mInputManager->GetButtonState(0, 7)) /* Player 1 Start button */)
		{
			currentScreen = play;
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame(mStartScreen->GetSelectMode());
		}
		break;
	case play:
		mPlayScreen->Update();
		if (mPlayScreen->GameOver())
		{
			currentScreen = start;
			mStartScreen->ResetAnimation();
		}
		else if (mPlayScreen->Victory())
		{
			currentScreen = ending;
			mStartScreen->ResetAnimation();
		}
		break;
	case ending:
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
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	case ending:
		break;
	default:
		break;
	}
}