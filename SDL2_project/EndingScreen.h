#pragma once
#include "StartScreen.h"

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
	
	std::vector<Texture*> mRanks;
	Texture* mTmpTexture = nullptr;

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

	bool mHighScoreUpdate;
	void UpdateHighScore();

	void Update();

	void Render();
};