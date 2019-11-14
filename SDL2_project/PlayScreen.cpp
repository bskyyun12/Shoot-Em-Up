#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mScoreBoard = new ScoreBoard();
	mStartLabel = new Texture("START!", Graphics::Instance()->FONT, 64, { 255, 20, 147 });
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
		mLifeTextures[i] = new Texture("heart.png");
		mLifeTextures[i]->Parent(mLives);
		mLifeTextures[i]->Scale(VECTOR2D_ONE * 0.8f);
		mLifeTextures[i]->Pos(mScoreBoard->mPlayerOne->Pos() + Vector2D(60.0f * (i % 3) + 120.0f, 70.0f * (i / 3)));
	}
	mTotalLives = 3;

	// level
	mLevel = nullptr;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 1.0f;
	mGameStarted = true;
	mLevelStarted = false;
	mCurrentStage = 0;
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

	// BottomBar
	//delete mBottomBarBackground;
	//mBottomBarBackground = nullptr;

	// Life
	delete mLives;
	mLives = nullptr;

	for (int i = 0; i < MAX_LIFE_TEXTURES; i++)
	{
		delete mLifeTextures[i];
		mLifeTextures[i] = nullptr;
	}
}

void PlayScreen::SetHighScore(int score)
{
	mScoreBoard->mHighScoreBoard->Score(score);
}

void PlayScreen::SetPlayerScore(int score)
{
	mScoreBoard->mPlayerOneScoreBoard->Score(score);
}

void PlayScreen::SetLives(int lives)
{
	mTotalLives = lives;
}

void PlayScreen::StartNextLevel()
{
	// test 3 - increse stage level and create new level instance
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage);
}

void PlayScreen::StartNewGame()
{
	BackgroundScroll::mScroll = false;
	SetHighScore(55555);
	SetLives(2);
	mGameStarted = false;
	mAudioManager->PlayMusic("Audios/drums.wav", 0);
	mCurrentStage = 0;
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
		// here do something after game starts before level starts(currently for 1 seconds)
	}
	else
	{
		// test 1 - game enter music start
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
			//BackgroundScroll::mScroll = true;
		}
	}

	if (mGameStarted && mLevelStarted)
	{
		mLevel->Update();
	}

	// Blinker logic
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		m1UPVisible = !m1UPVisible;
		mBlinkTimer = 0.0f;
	}

	// test purpose
	if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		StartNextLevel();
	}
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
	else
	{
		mScoreBoard->Render();
		for (int i = 0; i < MAX_LIFE_TEXTURES && i < mTotalLives; i++)
		{
			mLifeTextures[i]->Render();
		}
	}

	if (mGameStarted && mLevelStarted)
	{
		mLevel->Render();
	}

	// BottomBar
	//mBottomBarBackground->Render();


}
