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

	float mBlinkTimer;
	float mBlinkInterval;
	bool m1UPVisible;

public:

	PlayScreen();
	~PlayScreen();

	void SetHighScore(int score);
	void SetPlayerScore(int score);

	void Update();

	void Render();
};

