#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "BackgroundScroll.h"
#include "AudioManager.h"
#include "Player.h"
#include "Player2.h"
#include "Box.h"

class Level : public GameEntity
{
public:

	enum LEVEL_STATES
	{
		running, 
		finished, 
		gameover,
		victory
	};

private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	LEVEL_STATES mCurrentState;

	int mCurrentStage = 1;
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

<<<<<<< HEAD
	// Player - currently using this just to make it active
	Player* mPlayer = nullptr;
	Player2* mPlayer2 = nullptr;

	Box* mBox = nullptr;

=======
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
	// GameOverLabel
	Texture* mGameOverLabel = nullptr;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	// Victory
	bool mVictory;
	float mVictoryDelay;
	float mVictoryTimer;

	// Player - currently using this just to make it active
	Player* mPlayer = nullptr;
	Player2* mPlayer2 = nullptr;

	// Enemy
	std::vector<Box*> mBoxes;

private:

	void StartStage();
	void HandleStartLabels();

public:

	Level(int stage, Player* player, Player2* player2, Box* box);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();


};

