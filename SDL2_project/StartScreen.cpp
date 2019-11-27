#include "StartScreen.h"
#include "InputManager.h"

StartScreen::StartScreen()
{
	mBackgroundScroll = new BackgroundScroll();
	mBackgroundScroll->SetBackground("Backgrounds/space/Nebula_Red", 5);

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	//Top Bar
	mScoreBoard = ScoreBoard::Instance();
	mScoreBoard->Parent(this);

	// Logo Entities
	mLogo = new Texture("ship_80x48.png", 32, 0, 16, 24);
	mAnimatedLogo = new AnimatedTexture("ship_80x48.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);

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
	mCursor = new AnimatedTexture("ship_80x48.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mSelectMode = 1;

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2D(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2D(0.0f, 35.0f));
	mCursorPos1 = mOnePlayerMode->Pos(local) + Vector2D(-150.0f, 0);
	mCursorPos2 = mTwoPlayerMode->Pos(local) + Vector2D(-168.0f, 0);
	mCursor->Pos(mCursorPos1);

	mCursor->Scale(VECTOR2D_ONE * 1.3f);

	mPlayModes->Parent(this);

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mNamco = new Texture("namcot", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mDates = new Texture("1981 1985 NAMCO LTD.", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });

	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Pos(Vector2D(0.0f, 0.0f));
	mDates->Pos(Vector2D(0.0f, 90.0f));
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
	delete mCursor;
	mCursor = nullptr;

	//Freeing Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mNamco = nullptr;
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
	// Screen Animation Variables
	mAnimationStartPos = Vector2D((float)Graphics::Instance()->SCREEN_WIDTH * 0.5f, (float)Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VECTOR2D_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);

	mAudioManager->PlayMusic("Audios/intro_bmg.wav");
	mAudioManager->MusicVolume(10);
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
	if (change == 1)
	{
		mSelectMode = 1;
		mCursor->Pos(mCursorPos1);
	}
	else if (change == 2)
	{
		mSelectMode = 2;
		mCursor->Pos(mCursorPos2);
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

		if (mInputManager->KeyPressed(SDL_SCANCODE_UP) || mInputManager->KeyPressed(SDL_SCANCODE_DOWN))
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
			ChangeSelectedMode(1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN))
		{
			ChangeSelectedMode(2);
		}

		if (mInputManager->JoysticksInitialiased())
		{
			if (mInputManager->yValue(0, 1) < 0 || mInputManager->yValue(0, 2) < 0)
		   //|| mInputManager->xValue(0, 1) < 0 || mInputManager->xValue(0, 2) < 0)
			{
				ChangeSelectedMode(1);
			}
			else if (mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 2) > 0)
				//|| mInputManager->xValue(0, 1) > 0 || mInputManager->xValue(0, 2) > 0)
			{
				ChangeSelectedMode(2);
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
	mCursor->Render();

	//Render Bottom Bar Entities
	mNamco->Render();
	mDates->Render();
	mRights->Render();

}
