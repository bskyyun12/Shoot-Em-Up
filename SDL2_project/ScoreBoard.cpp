#include "ScoreBoard.h"

ScoreManager::ScoreManager()
{
	Score(0);
}

ScoreManager::~ScoreManager()
{
	ClearScore();
}

void ScoreManager::ClearScore()
{
	for (auto mScore : mScores)
	{
		delete mScore;
		mScore = nullptr;
	}

	mScores.clear();
}

void ScoreManager::Render()
{
	for (auto mScore : mScores)
	{
		mScore->Render();
	}
}

void ScoreManager::Score(int score)
{
	ClearScore();

	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScores.push_back(new Texture("0", Graphics::Instance()->FONT, 32, { 230, 230, 230 }));
			mScores[i]->Parent(this);
			mScores[i]->Pos(Vector2D(-32.0f * i, 0.0f));
		}
	}
	else
	{
		// t.e 1234
		std::string str = std::to_string(score); // "1234"
		int lastIndex = (int)str.length() - 1; // 4 - 1 = 3

		for (int i = 0; i <= lastIndex; i++)
		{
			// store each number of score 1, 2, 3, 4 -> in this way we can save memory since same text shares same cache
			mScores.push_back(new Texture(str.substr(i, 1), Graphics::Instance()->FONT, 32, { 230, 230, 230 }));
			mScores[i]->Parent(this); // 1, 2, 3, 4 ->Parent(this)
			mScores[i]->Pos(Vector2D(-32.0f * (lastIndex - i), 0.0f)); // start with last number and next one will be futher left then the previous one
		}
	}
}

ScoreBoard::ScoreBoard()
{
	//Top Bar Entities
	mTopBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 40.0f));
	mPlayerOne = new Texture("1UP", Graphics::Instance()->FONT, 32, { 0, 200, 0 });
	mPlayerTwo = new Texture("2UP", Graphics::Instance()->FONT, 32, { 0, 0, 200 });
	mHighScore = new Texture("High Score", Graphics::Instance()->FONT, 32, { 200, 0, 0 });
	mPlayerOneScoreBoard = new ScoreManager();
	mPlayerTwoScoreBoard = new ScoreManager();
	mHighScoreBoard = new ScoreManager();

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHighScore->Parent(mTopBar);
	mPlayerOneScoreBoard->Parent(mTopBar);
	mPlayerTwoScoreBoard->Parent(mTopBar);
	mHighScoreBoard->Parent(mTopBar);

	mPlayerOne->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * -0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.27f, 0.0f));
	mHighScore->Pos(Vector2D(0.0f, 0.0f));
	mPlayerOneScoreBoard->Pos(mPlayerOne->Pos(local) + Vector2D(0.0f, 32.0f));
	mPlayerTwoScoreBoard->Pos(mPlayerTwo->Pos(local) + Vector2D(0.0f, 32.0f));
	mHighScoreBoard->Pos(mHighScore->Pos(local) + Vector2D(0.0f, 32.0f));
	mHighScoreBoard->Score(123456);

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