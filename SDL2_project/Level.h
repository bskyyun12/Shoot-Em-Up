#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "BackgroundScroll.h"
#include "AudioManager.h"
#include "Player.h"
#include "NormalBullet.h"

class Level : public GameEntity
{
public:

public:

	enum LEVEL_STATES
	{
		running, 
		finished, 
		gameover
	};

private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	int mCurrentStage;
	bool mStageStarted;

	float mLabelTimer;

	// StageLabel
	Texture* mStageLabel = nullptr;
	ScoreManager* mStageNumber = nullptr;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	// ReadyLabel
	Texture* mReadyLabel = nullptr;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	// GoLabel
	Texture* mGoLabel = nullptr;
	float mGoLabelOnScreen;
	float mGoLabelOffScreen;

	// Player - currently using this just to make it active
	Player* mPlayer = nullptr;

	// GameOverLabel
	Texture* mGameOverLabel = nullptr;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

private:

	void StartStage();
	void HandleStartLabels();

public:

	Level(int stage, Player* player);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();


};

