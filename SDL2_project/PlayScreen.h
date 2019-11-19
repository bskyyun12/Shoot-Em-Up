#pragma once
#include "Level.h"

class PlayScreen : public GameEntity
{
private:

	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;
	ScoreBoard* mScoreBoard = nullptr;
	Texture* mStartLabel = nullptr;
	//Texture* mBottomBarBackground = nullptr;

	// Blinker
	float mBlinkTimer;
	float mBlinkInterval;
	bool m1UPVisible;

	// Life
	static const int MAX_LIFE_TEXTURES = 3;
	GameEntity* mLives = nullptr;
	Texture* mLifeTextures[MAX_LIFE_TEXTURES] = { nullptr };
	int mTotalLives;

	// level
	Level* mLevel = nullptr;
	float mLevelStartTimer;
	float mLevelStartDelay;
	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentStage;
	                    
	// Player
	Player* mPlayer = nullptr;
	Player2* mPlayer2 = nullptr;

	// background
	BackgroundScroll* mBackgroundScroll = nullptr;

private:

	void StartNextLevel();

public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame(int mSelectMode);

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetLives(int lives);

	int GetCurrentStageNum();

	bool GameOver();

	bool Victory();

	void Update();

	void Render();
};

