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

	// level
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
}

PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mScoreBoard;
	mScoreBoard = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

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
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
}

void PlayScreen::StartNewGame()
{
	BackgroundScroll::mScroll = false;
	SetHighScore(55555);
	SetLives(2);
	mGameStarted = false;
	mAudioManager->PlayMusic("Audios/ready_set_go.wav", 0);
	mCurrentStage = 0;
}

void PlayScreen::Update()
{
	// Blinker logic
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		m1UPVisible = !m1UPVisible;
		mBlinkTimer = 0.0f;
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

	// BottomBar
	//mBottomBarBackground->Render();


}
