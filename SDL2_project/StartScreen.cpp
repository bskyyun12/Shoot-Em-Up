#include "StartScreen.h"

StartScreen::StartScreen()
{
	mBackgroundScroll = new BackgroundScroll();
	mBackgroundScroll->SetBackground("Backgrounds/space/Nebula_Red", 5);

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	//Top Bar
	mScoreBoard = ScoreBoard::Instance();

	// Logo Entities
	mLogo = new Texture("shipRed.png", 32, 0, 16, 24);
	mAnimatedLogo = new AnimatedTexture("shipRed.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);

	mLogo->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));
	mAnimatedLogo->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

	mLogo->Scale(VECTOR2D_ONE * 4);
	mAnimatedLogo->Scale(VECTOR2D_ONE * 4);

	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	//Play Mode Entities
	mPlayModes = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mOnePlayerMode = new Texture("1 Player", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("2 Players", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mCredit = new Texture("Credits", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mKeysOption = new Texture("Keys & Option", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mCursor = new AnimatedTexture("shipRed.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mSelectMode = 1;

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCredit->Parent(mPlayModes);
	mKeysOption->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2D(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2D(0.0f, 35.0f));
	mCredit->Pos(Vector2D(-32.0f, 105.0f));
	mKeysOption->Pos(Vector2D(64.0f, 175.0f));
	mCursorPos1 = mOnePlayerMode->Pos(local) + Vector2D(-150.0f, 0);
	mCursorPos2 = mTwoPlayerMode->Pos(local) + Vector2D(-168.0f, 0);
	mCursorPos3 = mCredit->Pos(local) + Vector2D(-136.0f, 0);
	mCursorPos4 = mKeysOption->Pos(local) + Vector2D(-232.0f, 0);
	mCursor->Pos(mCursorPos1);

	mCursor->Scale(VECTOR2D_ONE * 1.3f);

	mPlayModes->Parent(this);

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mDates = new Texture("2019 FUTUREGAMES", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS WAIVED", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });

	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mDates->Pos(Vector2D(0.0f, 130.0f));
	mRights->Pos(Vector2D(0.0f, 180.0f));

	mBottomBar->Parent(this);

	ResetAnimation();

}

StartScreen::~StartScreen()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;
	mScoreBoard = nullptr;

	//Freeing Logo Entities
	delete mLogo;
	mLogo = nullptr;
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = nullptr;
	delete mOnePlayerMode;
	mOnePlayerMode = nullptr;
	delete mTwoPlayerMode;
	mTwoPlayerMode = nullptr;
	delete mCredit;
	mCredit = nullptr;
	delete mKeysOption;
	mKeysOption = nullptr;
	delete mCursor;
	mCursor = nullptr;

	//Freeing Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mRights;
	mRights = nullptr;

	// Background
	delete mBackgroundScroll;
	mBackgroundScroll = nullptr;
}

void StartScreen::ResetAnimation()
{
	mScoreBoard->Parent(this);

	// Screen Animation Variables
	mAnimationStartPos = Vector2D((float)Graphics::Instance()->SCREEN_WIDTH * 0.5f, (float)Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VECTOR2D_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);

	mAudioManager->PlayMusic("Audios/intro_bmg.wav");
	mAudioManager->MusicVolume(20);
}

bool StartScreen::IsAnimationDone()
{
	return mAnimationDone;
}

int StartScreen::GetSelectMode()
{
	return mSelectMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	if (change == 1 || change == 5)
	{
		mSelectMode = 1;
		mCursor->Pos(mCursorPos1);
	}
	else if (change == 2)
	{
		mSelectMode = 2;
		mCursor->Pos(mCursorPos2);
	}
	else if (change == 3)
	{
		mSelectMode = 3;
		mCursor->Pos(mCursorPos3);
	}
	else if (change == 4 || change == 0)
	{
		mSelectMode = 4;
		mCursor->Pos(mCursorPos4);
	}
}

void StartScreen::Update()
{
	mBackgroundScroll->Update();

	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_UP) || mInputManager->KeyPressed(SDL_SCANCODE_DOWN) || mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else
	{
		mScoreBoard->Parent(nullptr);
		mAnimatedLogo->Update();
		mCursor->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_UP))
		{
			mSelectMode--;
			ChangeSelectedMode(mSelectMode);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN))
		{
			mSelectMode++;
			ChangeSelectedMode(mSelectMode);
		}

		if (mInputManager->JoysticksInitialiased())
		{
			if (mInputManager->yValue(0, 1) < 0 || mInputManager->yValue(0, 2) < 0)
				//|| mInputManager->xValue(0, 1) < 0 || mInputManager->xValue(0, 2) < 0)
			{
				mSelectMode--;
				ChangeSelectedMode(mSelectMode);
			}
			else if (mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 2) > 0)
				//|| mInputManager->xValue(0, 1) > 0 || mInputManager->xValue(0, 2) > 0)
			{
				mSelectMode++;
				ChangeSelectedMode(mSelectMode);
			}
		}
	}
}

void StartScreen::Render()
{
	// Render background
	mBackgroundScroll->Render();

	//Render Top Bar
	mScoreBoard->Render();

	//Render Logo Entities
	if (!mAnimationDone)
	{
		mLogo->Render();
	}
	else
	{
		mAnimatedLogo->Render();
		mCursor->Render();
	}

	//Render Play Mode Entities
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCredit->Render();
	mKeysOption->Render();

	//Render Bottom Bar Entities
	mDates->Render();
	mRights->Render();

}
