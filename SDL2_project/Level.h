#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "BackgroundScroll.h"
#include "AudioManager.h"
#include "Player.h"

class Level : public GameEntity
{
public:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	int mCurrentStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel = nullptr;
	ScoreManager* mStageNumber = nullptr;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture* mReadyLabel = nullptr;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mGoLabel = nullptr;
	float mGoLabelOnScreen;
	float mGoLabelOffScreen;

	// Player - currently using this just to make it active
	Player* mPlayer = nullptr;

private:

	void StartStage();

public:

	Level(int stage, Player* player);
	~Level();

	void Update();
	void Render();


};

