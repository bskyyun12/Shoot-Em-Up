#include "KeyOptionScreen.h"

KeyOptionScreen::KeyOptionScreen()
{
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mBackgroundScroll = new BackgroundScroll();
	mBackgroundScroll->SetBackground("Backgrounds/space/Nebula_Red", 5);

	// Key Bar Entities
	mKeyBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.1f));
	// Player 1
	mPlayer1Key = new Texture("Player 1", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mPlayer1Key->Parent(mKeyBar);
	mPlayer1Key->Pos(Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	mPlayer1Move = new Texture("[ Arrow keys ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer1Move->Parent(mPlayer1Key);
	mPlayer1Move->Pos(Vector2D(0.0f, 90.0f));
	mPlayer1Fire = new Texture("[     P      ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer1Fire->Parent(mPlayer1Key);
	mPlayer1Fire->Pos(Vector2D(0.0f, 180.0f));
	mPlayer1Bomb = new Texture("[   R-Ctrl   ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer1Bomb->Parent(mPlayer1Key);
	mPlayer1Bomb->Pos(Vector2D(0.0f, 270.0f));
	mPlayer1Shield = new Texture("[   R-Shift  ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer1Shield->Parent(mPlayer1Key);
	mPlayer1Shield->Pos(Vector2D(0.0f, 360.0f));
	// Player 2
	mPlayer2Key = new Texture("Player 2", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mPlayer2Key->Parent(mKeyBar);
	mPlayer2Key->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	mPlayer2Move = new Texture("[  W A S D  ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer2Move->Parent(mPlayer2Key);
	mPlayer2Move->Pos(Vector2D(0.0f, 90.0f));
	mPlayer2Fire = new Texture("[   Space   ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer2Fire->Parent(mPlayer2Key);
	mPlayer2Fire->Pos(Vector2D(0.0f, 180.0f));
	mPlayer2Bomb = new Texture("[  L-Ctrl   ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer2Bomb->Parent(mPlayer2Key);
	mPlayer2Bomb->Pos(Vector2D(0.0f, 270.0f));
	mPlayer2Shield = new Texture("[  L-Shift  ]", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mPlayer2Shield->Parent(mPlayer2Key);
	mPlayer2Shield->Pos(Vector2D(0.0f, 360.0f));
	// Middle Bar
	mMove = new Texture("Move", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });
	mMove->Parent(mKeyBar);
	mMove->Pos(Vector2D(0.0f, 90.0f));
	mFire = new Texture("Fire", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });
	mFire->Parent(mKeyBar);
	mFire->Pos(Vector2D(0.0f, 180.0f));
	mBomb = new Texture("Bomb", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });
	mBomb->Parent(mKeyBar);
	mBomb->Pos(Vector2D(0.0f, 270.0f));
	mShield = new Texture("Shield", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });
	mShield->Parent(mKeyBar);
	mShield->Pos(Vector2D(0.0f, 360.0f));

	// Option Bar Entities
	mOptionBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	// Music
	mMusic = new Texture("Music", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mMusic->Parent(mOptionBar);
	mMusic->Pos(Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	mMusicOn = new Texture(" On ", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mMusicOn->Parent(mOptionBar);
	mMusicOn->Pos(mMusic->Pos(local) + Vector2D(0.0f, 90.0f));
	mMusicOff = new Texture(" Off", Graphics::Instance()->FONT_Emulogic, 32, { 100, 100, 100 });
	mMusicOff->Parent(mOptionBar);
	mMusicOff->Pos(mMusic->Pos(local) + Vector2D(0.0f, 90.0f));
	// SFX
	mSFX = new Texture("SFX", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mSFX->Parent(mOptionBar);
	mSFX->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	mSFXOn = new Texture(" On ", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mSFXOn->Parent(mOptionBar);
	mSFXOn->Pos(mSFX->Pos(local) + Vector2D(0.0f, 90.0f));
	mSFXOff = new Texture(" Off", Graphics::Instance()->FONT_Emulogic, 32, { 100, 100, 100 });
	mSFXOff->Parent(mOptionBar);
	mSFXOff->Pos(mSFX->Pos(local) + Vector2D(0.0f, 90.0f));

	mBack = new Texture("Back", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mBack->Parent(mOptionBar);
	mBack->Pos(Vector2D(0.0f, 180.0f));

	mCursor = new AnimatedTexture("shipRed.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mCursorPos1 = mMusicOn->Pos(local) + Vector2D(-60.0f, 0);
	mCursorPos2 = mSFXOn->Pos(local) + Vector2D(-60.0f, 0);
	mCursorPos3 = mBack->Pos(local) + Vector2D(-90.0f, 0);
	mCursor->Parent(mOptionBar);
	mCursor->Pos(mCursorPos1);
	mCursor->Scale(VECTOR2D_ONE * 1.3f);

	mSelectMode = 1;
	mReturn = false;
	mIsMusicOn = true;
	mIsSFXOn = true;
}

KeyOptionScreen::~KeyOptionScreen()
{
	mInputManager = nullptr;
	mAudioManager = nullptr;

	// Background
	delete mBackgroundScroll;
	mBackgroundScroll = nullptr;

	// Freeing Key Bar Entities
	delete mKeyBar;
	mKeyBar = nullptr;

	delete mPlayer1Key;
	mPlayer1Key = nullptr;
	delete mPlayer1Move;
	mPlayer1Move = nullptr;
	delete mPlayer1Fire;
	mPlayer1Fire = nullptr;
	delete mPlayer1Bomb;
	mPlayer1Bomb = nullptr;
	delete mPlayer1Shield;
	mPlayer1Shield = nullptr;

	delete mPlayer2Key;
	mPlayer2Key = nullptr;
	delete mPlayer2Move;
	mPlayer2Move = nullptr;
	delete mPlayer2Fire;
	mPlayer2Fire = nullptr;
	delete mPlayer2Bomb;
	mPlayer2Bomb = nullptr;
	delete mPlayer2Shield;
	mPlayer2Shield = nullptr;

	delete mMove;
	mMove = nullptr;
	delete mFire;
	mFire = nullptr;
	delete mBomb;
	mBomb = nullptr;
	delete mShield;
	mShield = nullptr;

	// Option Bar Entities
	delete mOptionBar;
	mOptionBar = nullptr;

	delete mMusic;
	mMusic = nullptr;
	delete mMusicOn;
	mMusicOn = nullptr;
	delete mMusicOff;
	mMusicOff = nullptr;

	delete mSFX;
	mSFX = nullptr;
	delete mSFXOn;
	mSFXOn = nullptr;
	delete mSFXOff;
	mSFXOff = nullptr;

	delete mBack;
	mBack = nullptr;

	delete mCursor;
	mCursor = nullptr;
}

void KeyOptionScreen::ChangeSelectedMode(int change)
{
	if (change == 1 || change == 4)
	{
		mSelectMode = 1;
		mCursor->Pos(mCursorPos1);
	}
	else if (change == 2)
	{
		mSelectMode = 2;
		mCursor->Pos(mCursorPos2);
	}
	else if (change == 3 || change == 0)
	{
		mSelectMode = 3;
		mCursor->Pos(mCursorPos3);
	}
}

bool KeyOptionScreen::Return()
{
	return mReturn;
}

void KeyOptionScreen::Update()
{
	mBackgroundScroll->Update();
	mCursor->Update();

	if (mInputManager->KeyPressed(SDL_SCANCODE_LEFT) || mInputManager->KeyPressed(SDL_SCANCODE_UP))
		ChangeSelectedMode(1);
	else if (mInputManager->KeyPressed(SDL_SCANCODE_RIGHT))
		ChangeSelectedMode(2);
	else if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN))
		ChangeSelectedMode(3);

	if (mInputManager->JoysticksInitialiased())
	{
		if (mInputManager->yValue(0, 1) < 0 || mInputManager->yValue(0, 2) < 0)
		{
			mSelectMode--;
			ChangeSelectedMode(mSelectMode);
		}
		else if (mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 2) > 0)
		{
			mSelectMode++;
			ChangeSelectedMode(mSelectMode);
		}
	}

	if (mSelectMode == 1 && mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		mIsMusicOn = !mIsMusicOn;
		if (!mIsMusicOn)
			mAudioManager->PauseMusic();
		else
			mAudioManager->ResumeMusic();
	}
	else if (mSelectMode == 2 && mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		mIsSFXOn = !mIsSFXOn;
		if (!mIsSFXOn)
			mAudioManager->PauseSFX();
		else
			mAudioManager->ResumeSFX();
	}
	else if (mSelectMode == 3 && mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		mReturn = true;
	}
	else 
	{
		mReturn = false;
	}
}

void KeyOptionScreen::Render()
{
	// Render background
	mBackgroundScroll->Render();

	//Render Bar Entities
	mPlayer1Key->Render();
	mPlayer1Move->Render();
	mPlayer1Fire->Render();
	mPlayer1Bomb->Render();
	mPlayer1Shield->Render();

	mPlayer2Key->Render();
	mPlayer2Move->Render();
	mPlayer2Fire->Render();
	mPlayer2Bomb->Render();
	mPlayer2Shield->Render();

	mMove->Render();
	mFire->Render();
	mBomb->Render();
	mShield->Render();

	//Render Option Bar Entities
	mMusic->Render();
	if (mIsMusicOn)
		mMusicOn->Render();
	else
		mMusicOff->Render();

	mSFX->Render();
	if (mIsSFXOn)
		mSFXOn->Render();
	else
		mSFXOff->Render();

	mBack->Render();

	mCursor->Render();
}
