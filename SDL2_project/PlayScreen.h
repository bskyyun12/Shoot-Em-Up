#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "InputManager.h"
#include "AudioManager.h"

class PlayScreen : public GameEntity
{
private:

	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	ScoreBoard* mScoreBoard = nullptr;
	Texture* mBottomBarBackground = nullptr;

	// Blinker
	float mBlinkTimer;
	float mBlinkInterval;
	bool m1UPVisible;

	// Life
	static const int MAX_LIFE_TEXTURES = 3;
	GameEntity* mLifes = nullptr;
	Texture* mLifeTextures[MAX_LIFE_TEXTURES];
	int mTotalLifes;

public:

	PlayScreen();
	~PlayScreen();

	void SetHighScore(int score);
	void SetPlayerScore(int score);

	void Update();

	void Render();
};

