#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mScoreBoard = new ScoreBoard();
	mStartLabel = new Texture("START!", Graphics::Instance()->FONT_Emulogic, 64, { 255, 20, 147 });
	mStartLabel->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	// BottomBar                                                           
	//float imageSize = 64;
	//float scaleValue = 0.05f;
	//mBottomBarBackground = new Texture("plx-1.png", 0, 0, (int)imageSize, (int)imageSize);
	//mBottomBarBackground->Parent(this);
	//mBottomBarBackground->Scale(Vector2D(Graphics::Instance()->SCREEN_WIDTH / imageSize, (Graphics::Instance()->SCREEN_WIDTH / imageSize) * scaleValue));
	//float imageHeight = imageSize * (Graphics::Instance()->SCREEN_WIDTH / imageSize) * scaleValue;
	//mBottomBarBackground->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT - imageHeight * 0.5f));

	// Blinker varialbles initializing
	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	m1UPVisible = true;

	// Life
	mLives = new GameEntity();
	mLives->Parent(mScoreBoard);
	mLives->Pos(Vector2D(0.0f, 0.0f));

	for (int i = 0; i < MAX_LIFE_TEXTURES; i++)
	{
		// Player 1
		mLifeTextures[i] = new Texture("HeartOrange.png");
		mLifeTextures[i]->Parent(mLives);
		mLifeTextures[i]->Scale(VECTOR2D_ONE * 0.5f);
		mLifeTextures[i]->Pos(mScoreBoard->mPlayerOne->Pos() + Vector2D(60.0f * (i % 3) + 120.0f, 70.0f * (i / 3)));

		// Player 2
		mLifeTextures2[i] = new Texture("HeartBlue.png");
		mLifeTextures2[i]->Parent(mLives);
		mLifeTextures2[i]->Scale(VECTOR2D_ONE * 0.5f);
		mLifeTextures2[i]->Pos(mScoreBoard->mPlayerTwo->Pos() + Vector2D(60.0f * (i % 3) + 120.0f, 70.0f * (i / 3)));
	}
	mTotalLives = 3;

	// level
	mLevel = nullptr;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 1.0f;
	mGameStarted = true;
	mLevelStarted = false;
	mCurrentStage = 0;

	// Player
	mPlayer = nullptr;
	mPlayer2 = nullptr;

	// background
	mBackgroundScroll = new BackgroundScroll();
}

PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mScoreBoard;
	mScoreBoard = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mPlayer2;
	mPlayer2 = nullptr;

	// Life
	delete mLives;
	mLives = nullptr;

	for (int i = 0; i < MAX_LIFE_TEXTURES; i++)
	{
		delete mLifeTextures[i];
		mLifeTextures[i] = nullptr;
		delete mLifeTextures2[i];
		mLifeTextures2[i] = nullptr;
	}

	// Background
	delete mBackgroundScroll;
	mBackgroundScroll = nullptr;
}

void PlayScreen::SetHighScore(int score)
{
	mScoreBoard->mHighScoreBoard->Score(score);
}

void PlayScreen::SetPlayerScore(int scorePlayer1, int scorePlayer2)
{
	mScoreBoard->mPlayerOneScoreBoard->Score(scorePlayer1);
	mScoreBoard->mPlayerTwoScoreBoard->Score(scorePlayer2);
}

void PlayScreen::SetLives(int lives)
{
	mTotalLives = lives;
}

int PlayScreen::GetCurrentStageNum()
{
	return mCurrentStage;
}

void PlayScreen::StartNextLevel()
{
	// test 3 - increse stage level and create new level instance
	mCurrentStage++;
	if (mCurrentStage > 9)
	{
		mCurrentStage = 1;
	}
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	// background change
	switch (mCurrentStage)
	{
	case 1:
		mPlayer->ToggleTexture(); // Change to mPlayerShip texture
		if (mPlayer2 != nullptr)
		{
			mPlayer2->ToggleTexture(); // Change to mPlayerShip2 texture
		}
		mBackgroundScroll->SetBackground("Backgrounds/space/Nebula_Red", 5);
		break;
	case 2:
		mBackgroundScroll->SetBackground("Backgrounds/mountain/mountain", 5);
		break;
	case 3:
		mPlayer->ToggleTexture(); // Change to mPlayer texture
		if (mPlayer2 != nullptr)
		{
			mPlayer2->ToggleTexture(); // Change to mPlayer2 texture
		}
		mBackgroundScroll->SetBackground("Backgrounds/demon/demon_woods", 4);
		break;
	case 4:
		mBackgroundScroll->SetBackground("Backgrounds/cyberpunk/cyberpunk", 3);
		break;
	case 5:
		mPlayer->ToggleTexture(); // Change to mPlayerShip texture
		if (mPlayer2 != nullptr)
		{
			mPlayer2->ToggleTexture(); // Change to mPlayerShip2 texture
		}
		mBackgroundScroll->SetBackground("Backgrounds/spaceblue/Nebula_Blue", 5);
		break;
	case 6:
		mBackgroundScroll->SetBackground("Backgrounds/spacepink/Nebula_Pink", 5);
		break;
	case 7:
		mBackgroundScroll->SetBackground("Backgrounds/planets/planets", 5);
		break;
	case 8:
		mPlayer->ToggleTexture(); // Change to mPlayer texture
		if (mPlayer2 != nullptr)
		{
			mPlayer2->ToggleTexture(); // Change to mPlayer2 texture
		}
		mBackgroundScroll->SetBackground("Backgrounds/yellowforest/yellowforest", 4);
		break;
	case 9:
		mBackgroundScroll->SetBackground("Backgrounds/forest/forest", 5);
		break;
	default:
		break;
	}

	// Create new Level
	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlayer, mPlayer2);
}

void PlayScreen::StartNewGame(int mSelectMode)
{
	// Create new Players
	// Player 1
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.08f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	if (mSelectMode == 2)
	{
		// Player 2
		delete mPlayer2;
		mPlayer2 = new Player2();
		mPlayer2->Parent(this);
		mPlayer2->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.08f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f + 100));
		mPlayer2->Active(false);
	}
	else
	{
		delete mPlayer2;
		mPlayer2 = nullptr;
	}

	SetHighScore(55555);
	SetLives(mPlayer->Lives());
	SetPlayerScore(mPlayer->Score(), (mSelectMode == 2) ? mPlayer2->Score() : 0);

	BackgroundScroll::mScroll = false;

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;

	mAudioManager->PlayMusic("Audios/playSceneStartDrum.wav", 0);
	mAudioManager->MusicVolume(10);
}

bool PlayScreen::GameOver()
{
	if (!mLevelStarted)
		return false;

	return (mLevel->State() == Level::gameover);
}

bool PlayScreen::Victory()
{
	if (!mLevelStarted)
		return false;

	return (mLevel->State() == Level::victory);
}

void PlayScreen::Update()
{
	// test 2 - wait mLevelStartDelay(1.0f) and start level
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}
		else
		{
			mBackgroundScroll->Update();
			mLevel->Update();
			if (mLevel->State() == Level::finished)
			{
				mLevelStarted = false;
			}

			mPlayer->Update();
			if (mPlayer2 != nullptr)
				mPlayer2->Update();
		}

		// here do something between game starts and level starts(currently for 1 seconds = mLevelStartDelay)

	}
	else
	{
		// if music is done, game starts
		if (!Mix_PlayingMusic())
			mGameStarted = true;
	}

	// Blinker logic
	//mBlinkTimer += mTimer->DeltaTime();
	//if (mBlinkTimer >= mBlinkInterval)
	//{
	//	m1UPVisible = !m1UPVisible;
	//	mBlinkTimer = 0.0f;
	//}
}

void PlayScreen::Render()
{
	// Blinker applying
	//if (m1UPVisible)
	//	mScoreBoard->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
	}

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mBackgroundScroll->Render();
			mLevel->Render();
			mScoreBoard->Render();
			for (int i = 0; i < MAX_LIFE_TEXTURES && i < mTotalLives; i++)
			{
				// Player 1
				mLifeTextures[i]->Render();
				// Player 2
				if (mPlayer2 != nullptr)
				{
					mLifeTextures2[i]->Render();
				}
			}

			mPlayer->Render();
			if (mPlayer2 != nullptr)
			{
				mPlayer2->Render();
			}
		}
	}
}
