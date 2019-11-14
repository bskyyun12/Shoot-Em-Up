#include "Level.h"

Level::Level(int stage)
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new Texture("STAGE", Graphics::Instance()->FONT, 64, { 255, 20, 147 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.45f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mStageNumber = new ScoreManager({ 255, 20, 147 }, 64);
	mStageNumber->Score(mStage);
	mStageNumber->Parent(this);
	mStageNumber->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.65f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.2f;

	mReadyLabel = new Texture("READY!", Graphics::Instance()->FONT, 64, { 255, 20, 147 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 1.1f;

	mGoLabel = new Texture("GO!!", Graphics::Instance()->FONT, 64, { 255, 20, 147 });
	mGoLabel->Parent(this);
	mGoLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGoLabelOnScreen = mReadyLabelOffScreen;
	mGoLabelOffScreen = mGoLabelOnScreen + 1.1f;

	mAudioManager->PlayMusic("Audios/ready_set_go.wav", 0);
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
}

void Level::StartStage()
{
	BackgroundScroll::mScroll = true;
	mStageStarted = true;
	mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
}

void Level::Update()
{
	if (!mStageStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		// wait until stage label is gone
		if (mLabelTimer >= mStageLabelOffScreen)
		{
			// if stage is not 1, wait until mStageLabelOffScreen (stage 10 -> StartStage)
			if (mStage > 1)
			{
				StartStage();
			}
			// if stage is 1, wait until mGoLabelOffScreen (stage 1 -> ready -> go -> StartStage)
			else
			{
				if (mLabelTimer >= mGoLabelOffScreen)
				{
					StartStage();
				}
			}
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
}