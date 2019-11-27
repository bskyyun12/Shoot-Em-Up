#include "Level.h"

Level::Level(int stage, Player* player, Player2* player2)
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();
	mAudioManager->PlayMusic("Audios/ready_set_go.wav", 0);

	mCurrentState = running;

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
	mGameOverLabelOnScreen = 1.5f;

	// Victory
	mVictoryLabel = new Texture("VICTORY!", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mVictoryLabel->Parent(this);
	mVictoryLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mVictory = false;
	mVictoryDelay = 6.0f;
	mVictoryTimer = 0.0f;
	mGameOverLabelOnScreen = 1.5f;

	// Player
	mPlayer = player;
	mPlayer->Active(false);
	mPlayer2 = player2;
	if (mPlayer2 != nullptr)
	{
		mPlayer2->Active(false);
	}

	// Enemy
	for (int i = 0; i < mCurrentStage; i++)
	{
		float ranX = (float)(rand() % 8 + 7) * 100; // 700 ~ 1400
		float ranY = (float)(rand() % 5 + 2) * 100; // 200 ~ 600
		mBoxes.push_back(new Box(Vector2D(ranX, ranY)));
	}
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

	delete mVictoryLabel;
	mVictoryLabel = nullptr;

	mPlayer = nullptr;
	mPlayer2 = nullptr;

	for (int i = 0; i < mBoxes.size(); i++)
	{
		delete mBoxes[i];
		mBoxes[i] = nullptr;
	}
}

void Level::StartStage()
{
	BackgroundScroll::mScroll = true;
	mStageStarted = true;

	switch (mCurrentStage)
	{
	case 1: // Nebula_Red
		mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
		break;
	case 2: // Mountain
		mAudioManager->PlayMusic("Audios/airship.wav");
		break;
	case 3: // Demon
		mAudioManager->PlayMusic("Audios/dark_fallout.wav"); // a bit low volume
		break;
	case 4: // Cyberpunk
		mAudioManager->PlayMusic("Audios/high_tech_lab.wav");
		break;
	case 5: // Nebula_Blue
		mAudioManager->PlayMusic("Audios/a_new_beginning.wav"); // low volume
		break;
	case 6: // Nebula_Pink
		mAudioManager->PlayMusic("Audios/eery.wav"); // low volume
		break;
	case 7: // Planets
		mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
		break;
	case 8: // yellowForest
		mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
		break;
	case 9: // Forest
		mAudioManager->PlayMusic("Audios/b_sean_retro.wav");
		break;
	default:
		break;
	}
	
	mPlayer->Active(true);
	if (mPlayer2 != nullptr)
	{
		mPlayer2->Active(true);
	}

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
		// todo: gameover condition
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X))
		{
			mGameOver = true;
			mAudioManager->PlaySFX("Audios/gameover0.wav", 0);
			mAudioManager->PlayMusic("Audios/gameover1.wav", 0); // low volume
		}

		// todo : victory condition
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V))
		{
			mVictory = true;
			mAudioManager->PlayMusic("Audios/victory.wav", 0);
		}

		// condition needs to be changed -> if all enemies have died,
		if (mBoxes.size() == 0 || InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
		{
			mAudioManager->PauseMusic();
			mAudioManager->PlayMusic("Audios/victory.wav", 0);
			mCurrentState = finished;
		}

		for (int i = 0; i < mBoxes.size(); i++)
		{
			if (!mBoxes[i]->Active())
			{
				delete mBoxes[i];
				mBoxes[i] = nullptr;
				mBoxes.erase(mBoxes.begin() + i);
			}
			else
			{
				mBoxes[i]->Update();
			}
		}
	}

	if (mGameOver)
	{
		// todo: play gameover sound
		mPlayer->Active(false);
		if (mPlayer2 != nullptr)
		{
			mPlayer2->Active(false);
		}

		mGameOverTimer += mTimer->DeltaTime();
		if (mGameOverTimer >= mGameOverDelay)
		{
			mCurrentState = gameover;
		}
	}

	// Victory
	if (mVictory)
	{
		// todo: play victory sound

		// here do somthing before game ends

		mVictoryTimer += mTimer->DeltaTime();
		if (mVictoryTimer >= mVictoryDelay)
		{
			mCurrentState = victory;
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
		for (int i = 0; i < mBoxes.size(); i++)
		{
			mBoxes[i]->Render();
		}

		if (mGameOver)
		{
			// wait 1.5 sec and display GAME OVER
			if (mGameOverTimer >= mGameOverLabelOnScreen)
			{
				mGameOverLabel->Render();
			}
		}

		if (mVictory)
		{
			// wait 1.5 sec and display VICTORY
			if (mGameOverTimer >= mVictoryLabelOnScreen)
			{
				mVictoryLabel->Render();
			}
		}
	}
}