#include "ScoreManager.h"

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
	for (unsigned int i = 0; i < HIGHSCORE_LIST_SIZE; i++)
	{
		// save to highscore vector
		mHighScores.push_back(GetHighScoreFromFileAtPosition(i));
	}
	SortHighScores();
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
	mCurrentPlayerScore = Player::Score();
	mCurrentPlayer2Score = Player2::Score();
	// save the players score to last position in vector and sort
	if (mCurrentPlayerScore > mHighScores[6])
	{
		mHighScores[6] = mCurrentPlayerScore;
		SortHighScores();
	}
	if (mCurrentPlayer2Score > mHighScores[6])
	{
		mHighScores[6] = mCurrentPlayer2Score;
		SortHighScores();
	}
	for (unsigned int i = 0; i < HIGHSCORE_LIST_SIZE; i++)
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