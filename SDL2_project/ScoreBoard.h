#pragma once
#include "Texture.h"
#include <vector>
#include <fstream> // Used for reading and writing highscore to a file
#include <iostream> // Used for debug
#include <algorithm> // Used for sorting highscores

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

	int mFontSize;

	SDL_Color mColor = { 0, 0, 0, 0 };

	unsigned int mHighScore = 0;

	std::vector<unsigned int> mHighScores;

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
	unsigned int GetHighScoreFromFileAtPosition(unsigned int pos);
	void WriteHighScoreToPosition(unsigned int pos);
	
private:

	void ClearScore();

};

class ScoreBoard : public GameEntity
{
private:
	static ScoreBoard* sInstance;

public:

	static ScoreBoard* Instance();
	static void Release();

	//Top Bar Entities
	GameEntity* mTopBar = nullptr;
	Texture* mPlayerOne = nullptr;
	Texture* mPlayerTwo = nullptr;
	Texture* mHighScore = nullptr;

	ScoreManager* mPlayerOneScoreBoard = nullptr;
	ScoreManager* mPlayerTwoScoreBoard = nullptr;
	ScoreManager* mHighScoreBoard = nullptr;

	static float mScoreBoardHeight;

public:

	static float GetScoreBoardHeight();

	void Render();

private:

	ScoreBoard();
	~ScoreBoard();

};

