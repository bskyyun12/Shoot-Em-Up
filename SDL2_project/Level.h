#pragma once
#include "InputManager.h"
#include "Timer.h"
#include "Texture.h"
#include "ScoreBoard.h"
#include "BackgroundScroll.h"
#include "AudioManager.h"

class Level : public GameEntity
{
public:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	int mStage;
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

private:

	void StartStage();

public:

	Level(int stage);
	~Level();

	void Update();
	void Render();


};

