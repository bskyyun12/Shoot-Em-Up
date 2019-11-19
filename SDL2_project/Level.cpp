#include "Level.h"

Level::Level(int stage, Player* player, Player2* player2)
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();
	mAudioManager->PlayMusic("Audios/ready_set_go.wav", 0);

	mCurrentStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	// StageLabel
	mStageLabel = new Texture("STAGE", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.45f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mStageNumber = new ScoreManager({ 255, 20, 147 }, 64);
	mStageNumber->Score(mCurrentStage);
	mStageNumber->Parent(this);
	mStageNumber->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.65f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.2f;

	// ReadyLabel
	mReadyLabel = new Texture("READY!", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 1.1f;

	// GoLabel
	mGoLabel = new Texture("GO!!", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mGoLabel->Parent(this);
	mGoLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGoLabelOnScreen = mReadyLabelOffScreen;
	mGoLabelOffScreen = mGoLabelOnScreen + 1.1f;

	// GameOverLabel
	mGameOverLabel = new Texture("GAME OVER!", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;

	// Player
	mPlayer = player;
	mPlayer->Active(false);
	mPlayer2 = player2;
	mPlayer2->Active(false);

}

Level::~Level()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;

	delete mStageNumber;
	mStageNumber = nullptr;

	delete mReadyLabel;
	mReadyLabel = nullptr;

	delete mGoLabel;
	mGoLabel = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	mPlayer = nullptr;
	mPlayer2 = nullptr;
}

void Level::StartStage()
{
	BackgroundScroll::mScroll = true;
	mStageStarted = true;
	mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
	mPlayer->Active(true);
	mPlayer2->Active(true);
	mLabelTimer = 0.0f;
}

void Level::HandleStartLabels()
{
	mLabelTimer += mTimer->DeltaTime();
	// wait until stage label is gone
	if (mLabelTimer >= mStageLabelOffScreen)
	{
		// Display STAGE and start game directly
		if (mCurrentStage > 1)
		{
			StartStage();
		}
		// Display STAGE READY GO and start game
		else
		{
			if (mLabelTimer >= mGoLabelOffScreen)
			{
				StartStage();
			}
		}
	}
}

Level::LEVEL_STATES Level::State()
{
	return mCurrentState;
}

void Level::Update()
{

	if (!mStageStarted)
	{
		HandleStartLabels();
	}
	else
	{
		// gameover labels
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X))
		{
			mGameOver = true;
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
		{
			mCurrentState = finished;
		}
	}

	if (mGameOver)
	{
		// todo: play gameover sound
		mPlayer->Active(false);
		mPlayer2->Active(false);

		mGameOverTimer += mTimer->DeltaTime();
		if (mGameOverTimer >= mGameOverDelay)
		{
			mCurrentState = gameover;
		}
	}
}

void Level::Render()
{
	if (!mStageStarted)
	{
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen)
		{
			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen)
		{
			mReadyLabel->Render();
		}
		else if (mLabelTimer > mGoLabelOnScreen && mLabelTimer < mGoLabelOffScreen)
		{
			mGoLabel->Render();
		}
	}
	else
	{
		if (mGameOver)
		{
			// wait 1 sec and display GAME OVER
			if (mGameOverTimer >= mGameOverLabelOnScreen)
			{
				mGameOverLabel->Render();
			}
		}
	}
}