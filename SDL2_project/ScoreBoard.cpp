#include "ScoreBoard.h"

ScoreManager::ScoreManager() : ScoreManager({ 230, 230, 230 }, 32)
{}

ScoreManager::ScoreManager(SDL_Color color, int fontSize)
{
	mColor = color;
	Score(0);
	mFontSize = fontSize;
}

ScoreManager::~ScoreManager()
{
	ClearScore();
}

void ScoreManager::ReadHighScoresFromFile()
{
	std::string mHighScoreString;
	for (unsigned int i = 0; i < 7; i++)
	{
		// save to highscore vector
		mHighScores.push_back(GetHighScoreFromFileAtPosition(i));
		SortHighScores();
	}
	mHighScore = mHighScores[0]; // save first place highscore
}

unsigned int ScoreManager::GetHighScoreFromFileAtPosition(unsigned int pos)
{
	std::cout << "Reading " << pos << " HighScore from file" << std::endl;
	std::string mHighScoreString;
	std::ifstream mHighScoreFile("highscore" + std::to_string(pos) + ".txt");
	if (mHighScoreFile.is_open())
	{
		getline(mHighScoreFile, mHighScoreString);
		mHighScoreFile.close();
	}
	return std::stoi(mHighScoreString); // convert string to int
}

void ScoreManager::WriteHighScoreToFile()
{
	// save the new highest highscore to last position in vector
	if (mHighScore > mHighScores[0])
	{
		mHighScores[6] = mHighScore;
	}
	SortHighScores();
	for (unsigned int i = 0; i < 7; i++)
	{
		WriteHighScoreToPosition(i);
	}
}

void ScoreManager::WriteHighScoreToPosition(unsigned int pos)
{
	std::cout << "Writing " << pos << " HighScore to file" << std::endl;
	std::ofstream mHighScoreFile("highscore" + std::to_string(pos) + ".txt");
	if (mHighScoreFile.is_open())
	{
		mHighScoreFile << mHighScores[pos];
		mHighScoreFile.close();
	}
}

unsigned int ScoreManager::GetHighScoreAtPosition(unsigned int pos)
{
	return mHighScores[pos];
}

void ScoreManager::SortHighScores()
{
	std::sort(mHighScores.begin(), mHighScores.end(), std::greater<int>());
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

void ScoreManager::Score(unsigned int score)
{
	// Set current highscore
	if (score > mHighScore)
	{
		mHighScore = score;
	}

	ClearScore();

	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScores.push_back(new Texture("0", Graphics::Instance()->FONT_Emulogic, 32, mColor));
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
			mScores.push_back(new Texture(str.substr(i, 1), Graphics::Instance()->FONT_Emulogic, mFontSize, mColor));
			mScores[i]->Parent(this); // 1, 2, 3, 4 ->Parent(this)
			mScores[i]->Pos(Vector2D(-(float)mFontSize * (lastIndex - i) + (lastIndex * mFontSize * 0.5f), 0.0f)); // start with last number and next one will be futher left then the previous one
		}
	}
}

unsigned int ScoreManager::GetCurrentHighScore()
{
	return mHighScore;
}

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

	mPlayerOne->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * -0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.27f, 0.0f));
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