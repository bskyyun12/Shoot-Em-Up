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

	// Blinker
	float mBlinkTimer;
	float mBlinkInterval;
	bool m1UPVisible;

	// Life
	GameEntity* mLives = nullptr;
	static const int MAX_LIFE_TEXTURES = 3;
	int mPlayerLives;
	int mPlayer2Lives;

	// Player 1
	Texture* mLifeTextures[MAX_LIFE_TEXTURES] = { nullptr };
	// Player 2
	Texture* mLifeTextures2[MAX_LIFE_TEXTURES] = { nullptr };

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

	void SetHighScore(unsigned int score);
	unsigned int GetCurrentHighScore();
	void SetPlayerScore(unsigned int scorePlayer, unsigned int scorePlayer2);
	void SetLives(int playerlives, int player2lives);

	int GetCurrentStageNum();

	bool GameOver();

	bool Victory();

	void Update();

	void Render();
};

