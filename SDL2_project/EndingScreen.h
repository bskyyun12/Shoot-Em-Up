#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"
#include "AudioManager.h"
#include "BackgroundScroll.h"

class EndingScreen : public GameEntity
{
private:

	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	ScoreBoard* mScoreBoard = nullptr;

	//Middle Bar Entities
	GameEntity* mMiddleBar = nullptr;
	Texture* mTop10 = nullptr;

	//Bottom Bar Entities
	GameEntity* mBottomBar = nullptr;
	Texture* mCredit = nullptr;
	Texture* mNames = nullptr;
	AnimatedTexture* mFredrik = nullptr;
	AnimatedTexture* mGwangyeong = nullptr;
	AnimatedTexture* mMattias = nullptr;

	BackgroundScroll* mBackgroundScroll;

public:

	EndingScreen();
	~EndingScreen();

	void Update();

	void Render();

};
