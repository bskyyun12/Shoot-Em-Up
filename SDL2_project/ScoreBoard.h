#pragma once
#include "Texture.h"
#include <vector>

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

	int mCurrentScore;

	int mFontSize;

	SDL_Color mColor = { 0, 0, 0, 0 };

public:

	// Default color : white / Default fontSize : 32
	ScoreManager();

	// color : pass rgb color(t.e { 255, 20, 147 })
	// fontsize : 32 is default
	ScoreManager(SDL_Color color, int fontSize = 32);
	~ScoreManager();

	int GetScore();
	void SetScore(int score);

	void Render();

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

