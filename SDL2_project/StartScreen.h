#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

class StartScreen : public GameEntity
{
protected:

	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	//Top Bar
	ScoreBoard* mScoreBoard = nullptr;

	// Logo Entities
	Texture* mLogo = nullptr;
	AnimatedTexture* mAnimatedLogo = nullptr;

	//Play Mode Entities
	GameEntity* mPlayModes = nullptr;
	Texture* mOnePlayerMode = nullptr;
	Texture* mTwoPlayerMode = nullptr;
	AnimatedTexture* mCursor = nullptr;
	Vector2D mCursorPos1;
	Vector2D mCursorPos2;
	int mSelectMode;
	
	//Bottom Bar Entities
	GameEntity* mBottomBar = nullptr;
	Texture* mNamco = nullptr;
	Texture* mDates = nullptr;
	Texture* mRights = nullptr;

	// Screen Animation Variables
	Vector2D mAnimationStartPos;
	Vector2D mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

public:

	StartScreen();
	~StartScreen();

	void ResetAnimation();

	int SelectMode();
	void ChangeSeletedMode(int change);

	void Update();

	void Render();

	bool mTwoPlayers;

};

