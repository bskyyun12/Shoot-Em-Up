#pragma once
#include "Texture.h"
#include <vector>
#include <fstream> // Used for reading and writing highscore to a file
#include <iostream> // Used for debug

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

	int mFontSize;

	SDL_Color mColor = { 0, 0, 0, 0 };

	unsigned int mHighScore = 0;

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
	void ReadHighScoreFromFile();
	void WriteHighScoreToFile();

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

	void Render();

private:

	ScoreBoard();
	~ScoreBoard();

};

