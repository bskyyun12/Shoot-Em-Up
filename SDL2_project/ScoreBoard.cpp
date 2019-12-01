#include "ScoreBoard.h"

// mTopBar Y offset + mPlayerOneScoreBoard Y offset + half of score's font size
float ScoreBoard::mScoreBoardHeight = 40.0f + 32.0f + 16.0f;
ScoreBoard* ScoreBoard::sInstance = nullptr;

ScoreBoard* ScoreBoard::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new ScoreBoard();
	}
	return sInstance; 
}

void ScoreBoard::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScoreBoard::ScoreBoard()
{
	//Top Bar Entities
	mTopBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 40.0f));
	mPlayerOne = new Texture("1UP", Graphics::Instance()->FONT_Emulogic, 32, { 218, 94, 83 });
	mPlayerTwo = new Texture("2UP", Graphics::Instance()->FONT_Emulogic, 32, { 47, 172, 218 });
	mHighScore = new Texture("High Score", Graphics::Instance()->FONT_Emulogic, 32, { 200, 0, 0 });
	mPlayerOneScoreBoard = new ScoreManager();
	mPlayerTwoScoreBoard = new ScoreManager();
	mHighScoreBoard = new ScoreManager();

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHighScore->Parent(mTopBar);
	mPlayerOneScoreBoard->Parent(mTopBar);
	mPlayerTwoScoreBoard->Parent(mTopBar);
	mHighScoreBoard->Parent(mTopBar);

	mPlayerOne->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * -0.4f, 0.0f));
	mPlayerTwo->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.4f, 0.0f));
	mHighScore->Pos(Vector2D(0.0f, 0.0f));
	mPlayerOneScoreBoard->Pos(mPlayerOne->Pos(local) + Vector2D(0.0f, 32.0f));
	mPlayerTwoScoreBoard->Pos(mPlayerTwo->Pos(local) + Vector2D(0.0f, 32.0f));
	mHighScoreBoard->Pos(mHighScore->Pos(local) + Vector2D(0.0f, 32.0f));
	mHighScoreBoard->ReadHighScoresFromFile(); // Read highscore from file
	mHighScoreBoard->Score(mHighScoreBoard->GetCurrentHighScore()); // update score

	mTopBar->Parent(this);

}

ScoreBoard::~ScoreBoard()
{
	//Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHighScore;
	mHighScore = nullptr;
	delete mPlayerOneScoreBoard;
	mPlayerOneScoreBoard = nullptr;
	delete mPlayerTwoScoreBoard;
	mPlayerTwoScoreBoard = nullptr;
	delete mHighScoreBoard;
	mHighScoreBoard = nullptr;
}

float ScoreBoard::GetScoreBoardHeight()
{
	return mScoreBoardHeight;
}

void ScoreBoard::Render()
{
	//Render Top Bar Entities
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHighScore->Render();
	mPlayerOneScoreBoard->Render();
	mPlayerTwoScoreBoard->Render();
	mHighScoreBoard->Render();
}