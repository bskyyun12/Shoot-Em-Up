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
	SetHighScore(30000);
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

void PlayScreen::Update()
{

}

void PlayScreen::Render()
{
	mScoreBoard->Render();
	mBottomBarBackground->Render();
}
