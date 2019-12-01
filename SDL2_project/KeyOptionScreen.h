#pragma once
#include "StartScreen.h"

class KeyOptionScreen : public GameEntity
{
private:

	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	BackgroundScroll* mBackgroundScroll;
	
	// Key Bar Entities
	GameEntity* mKeyBar = nullptr;
	// Player1 bar
	Texture* mPlayer1Key = nullptr;
	Texture* mPlayer1Move = nullptr;
	Texture* mPlayer1Fire = nullptr;
	Texture* mPlayer1Bomb = nullptr;
	Texture* mPlayer1Shield = nullptr;
	// Player2 bar
	Texture* mPlayer2Key = nullptr;
	Texture* mPlayer2Move = nullptr;
	Texture* mPlayer2Fire = nullptr;
	Texture* mPlayer2Bomb = nullptr;
	Texture* mPlayer2Shield = nullptr;
	// Middle bar 
	Texture* mMove = nullptr;
	Texture* mFire = nullptr;
	Texture* mBomb = nullptr;
	Texture* mShield = nullptr;

	// Option Bar Entities
	GameEntity* mOptionBar = nullptr;

	Texture* mMusic = nullptr;
	Texture* mMusicOn = nullptr;
	Texture* mMusicOff = nullptr;

	Texture* mSFX = nullptr;
	Texture* mSFXOn = nullptr;
	Texture* mSFXOff = nullptr;

	Texture* mBack = nullptr;

	AnimatedTexture* mCursor = nullptr;

	Vector2D mCursorPos1;
	Vector2D mCursorPos2;
	Vector2D mCursorPos3;

	int mSelectMode;
	bool mReturn;
	bool mIsMusicOn;
	bool mIsSFXOn;

public:
	KeyOptionScreen();
	~KeyOptionScreen();

	void ChangeSelectedMode(int change);
	bool Return();

	void Update();

	void Render();
};

