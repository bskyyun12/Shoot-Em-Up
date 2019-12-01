#pragma once
#include "Texture.h"
#include <vector>
#include <fstream> // Used for reading and writing highscore to a file
#include <iostream> // Used for debug
#include <algorithm> // Used for sorting highscores
#include "Player.h"
#include "Player2.h"

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

	int mFontSize;

	SDL_Color mColor = { 0, 0, 0, 0 };

	unsigned int mHighScore = 0;
	unsigned int mCurrentPlayerScore;
	unsigned int mCurrentPlayer2Score;

	std::vector<unsigned int> mHighScores;
	unsigned static const int HIGHSCORE_LIST_SIZE = 7;

public:

	// Default color : white / Default fontSize : 32
	ScoreManager();

	// color : pass rgb color(t.e { 255, 20, 147 })
	// fontsize : 32 is default
	ScoreManager(SDL_Color color, int fontSize = 32);
	~ScoreManager();

	void Render();

	void Score(unsigned int score);

	unsigned int GetCurrentHighScore();
	unsigned int GetHighScoreAtPosition(unsigned int pos);
	void SortHighScores();

	// Read and write to highscore .txt files
	void ReadHighScoresFromFile();
	void WriteHighScoreToFile();
	
private:

	unsigned int GetHighScoreFromFileAtPosition(unsigned int pos);
	void WriteHighScoreToPosition(unsigned int pos);

	void ClearScore();

};
