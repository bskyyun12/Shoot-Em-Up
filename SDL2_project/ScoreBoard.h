#pragma once
#include "Texture.h"
#include <vector>

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

	int mFontSize;

	SDL_Color mColor = { 0, 0, 0, 0 };

public:

	ScoreManager();
	ScoreManager(SDL_Color color, int fontSize);
	~ScoreManager();

	void Score(int score);

	void Render();

private:

	void ClearScore();

};

class ScoreBoard : public GameEntity
{
private:

public:
	ScoreBoard();
	~ScoreBoard();

	//Top Bar Entities
	GameEntity* mTopBar = nullptr;
	Texture* mPlayerOne = nullptr;
	Texture* mPlayerTwo = nullptr;
	Texture* mHighScore = nullptr;

	ScoreManager* mPlayerOneScoreBoard = nullptr;
	ScoreManager* mPlayerTwoScoreBoard = nullptr;
	ScoreManager* mHighScoreBoard = nullptr;

	void Render();

};

