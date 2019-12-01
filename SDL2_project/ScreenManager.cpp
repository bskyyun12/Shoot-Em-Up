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
	mEndingScreen = new EndingScreen();
	mKeyOptionScreen = new KeyOptionScreen();

	currentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mEndingScreen;
	mEndingScreen = nullptr;

	delete mKeyOptionScreen;
	mKeyOptionScreen = nullptr;
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
		if (
			mStartScreen->IsAnimationDone() && mInputManager->KeyPressed(SDL_SCANCODE_RETURN) ||
		   (mStartScreen->IsAnimationDone() && mInputManager->JoysticksInitialiased() && /* Joysticks initialised */
		   (mInputManager->GetButtonState(0, 7) || /* Player 1 Start button */
			mInputManager->GetButtonState(0, 0)))/* Player 1 A button */
			) 
		{
			switch (mStartScreen->GetSelectMode())
			{
			case 1:
			case 2:
				currentScreen = play;
				mPlayScreen->StartNewGame(mStartScreen->GetSelectMode());
				break;
			case 3:
				currentScreen = ending;
				mEndingScreen->mHighScoreUpdate = false;
				break;
			case 4:
				currentScreen = keyOption;
				break;
			default:
				break;
			}
		}
		break;
	case play:
		mPlayScreen->Update();
		if (mPlayScreen->GameOver())
		{
			mStartScreen->ResetAnimation();
			currentScreen = start;
		}
		else if (mPlayScreen->Victory())
		{
			currentScreen = ending;
		}
		break;
	case ending:
		mEndingScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN) ||
			(mInputManager->JoysticksInitialiased() && /* Joysticks initialised */
			(mInputManager->GetButtonState(0, 7) || /* Player 1 Start button */
				mInputManager->GetButtonState(0, 0)))) /* Player 1 A button */
		{
			currentScreen = start;
			mStartScreen->ResetAnimation();
		}
		break;
	case keyOption:
		mKeyOptionScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN) ||
			(mInputManager->JoysticksInitialiased() && /* Joysticks initialised */
			(mInputManager->GetButtonState(0, 7) || /* Player 1 Start button */
				mInputManager->GetButtonState(0, 0)))) /* Player 1 A button */
		{
			if (mKeyOptionScreen->Return())
			{
				currentScreen = start;
				mStartScreen->ResetAnimation();
			}
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
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	case ending:
		mEndingScreen->Render();
		break;
	case keyOption:
		mKeyOptionScreen->Render();
		break;
	default:
		break;
	}
}