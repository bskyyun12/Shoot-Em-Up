#include "PlayScreen.h"
#include <iostream>

using std::cout;
using std::endl;

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
		mLifeTextures[i] = new Texture("HeartOrange.png");
		mLifeTextures[i]->Parent(mLives);
		mLifeTextures[i]->Scale(VECTOR2D_ONE * 0.5f);
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

	// Player
	mPlayer = nullptr;
	if (mPlayer2 != nullptr)
	{
		mPlayer2 = nullptr;
	}
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

	if (mPlayer2 != nullptr)
	{
		delete mPlayer2;
		mPlayer2 = nullptr;
	}

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

	// Create new Level
	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlayer, mPlayer2);
}

void PlayScreen::StartNewGame(int mSelectMode)
{
	cout << "mSelectMode : " << mSelectMode << endl;
	// Create new Players
	// Player 1
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.08f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	SetHighScore(55555);
	SetLives(mPlayer->Lives());
	SetPlayerScore(mPlayer->Score());

	if (mSelectMode == 2)
	{
		// Player 2
		delete mPlayer2;
		mPlayer2 = new Player2();
		mPlayer2->Parent(this);
		mPlayer2->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.08f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f + 100));
		mPlayer2->Active(false);

		SetHighScore(55555);
		SetLives(mPlayer2->Lives());
		SetPlayerScore(mPlayer2->Score());
	}

	BackgroundScroll::mScroll = false;

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;

	mAudioManager->PlayMusic("Audios/drums.wav", 0);
	mAudioManager->MusicVolume(10);
}

bool PlayScreen::GameOver()
{
	if (!mLevelStarted)
		return false;

	return (mLevel->State() == Level::gameover);
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
		// here do something between game starts and level starts(currently for 1 seconds = mLevelStartDelay)
	}
	else
	{
		// if music is done, game starts
		if (!Mix_PlayingMusic())
			mGameStarted = true;
	}

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Update();
			if (mLevel->State() == Level::finished)
			{
				mLevelStarted = false;
			}
		}

		mPlayer->Update();
		if (mPlayer2 != nullptr)
		{
			mPlayer2->Update();
		}
	}

	// Blinker logic
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		m1UPVisible = !m1UPVisible;
		mBlinkTimer = 0.0f;
	}

	// test purpose
	//if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	//{
	//	StartNextLevel();
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
	else
	{
		mScoreBoard->Render();
		for (int i = 0; i < MAX_LIFE_TEXTURES && i < mTotalLives; i++)
		{
			mLifeTextures[i]->Render();
		}
	}

	if (mGameStarted)
	{
		mPlayer->Render();
		if (mPlayer2 != nullptr)
		{
			mPlayer2->Render();
		}

		if (mLevelStarted)
			mLevel->Render();
	}

	// BottomBar
	//mBottomBarBackground->Render();


}
