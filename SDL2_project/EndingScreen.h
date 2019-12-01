#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"
#include "AudioManager.h"
#include "BackgroundScroll.h"

class EndingScreen : public GameEntity
{
private:

	BackgroundScroll* mBackgroundScroll;

	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	ScoreBoard* mScoreBoard = nullptr;

	//Middle Bar Entities
	GameEntity* mMiddleBar = nullptr;
	Texture* mTop7 = nullptr;
	Texture* mFirst = nullptr;
	Texture* mSecond = nullptr;
	Texture* mThird = nullptr;
	Texture* mFourth = nullptr;
	Texture* mFifth = nullptr;
	Texture* mSixth = nullptr;
	Texture* mSeventh = nullptr;

	//Bottom Bar Entities
	GameEntity* mBottomBar = nullptr;
	Texture* mCredit = nullptr;
	Texture* mNames = nullptr;
	AnimatedTexture* mFredrik = nullptr;
	AnimatedTexture* mGwangyeong = nullptr;
	AnimatedTexture* mMattias = nullptr;

public:

	EndingScreen();
	~EndingScreen();

	void Update();

	void Render();

};