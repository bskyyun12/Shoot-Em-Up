#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mScoreBoard = new ScoreBoard();

	float imageSize = 64;
	float scaleValue = 0.05f;
	mBottomBarBackground = new Texture("plx-1.png", 0, 0, (int)imageSize, (int)imageSize);
	mBottomBarBackground->Parent(this);
	mBottomBarBackground->Scale(Vector2D(Graphics::Instance()->SCREEN_WIDTH / imageSize, (Graphics::Instance()->SCREEN_WIDTH / imageSize) * scaleValue));
	float imageHeight = imageSize * (Graphics::Instance()->SCREEN_WIDTH / imageSize) * scaleValue;
	mBottomBarBackground->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT - imageHeight * 0.5f));
	//SetHighScore(30000);

	// Blinker varialbles initializing
	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	m1UPVisible = true;
}

PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mScoreBoard;
	mScoreBoard = nullptr;

	delete mBottomBarBackground;
	mBottomBarBackground = nullptr;
}

void PlayScreen::SetHighScore(int score)
{
	mScoreBoard->mHighScoreBoard->Score(score);
}

void PlayScreen::SetPlayerScore(int score)
{
	mScoreBoard->mPlayerOneScoreBoard->Score(score);
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
	if (m1UPVisible)
		mScoreBoard->Render();
	mBottomBarBackground->Render();
}
