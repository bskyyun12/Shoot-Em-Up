#pragma once
#include "Texture.h"
#include <vector>

class ScoreManager : public GameEntity
{
private:

	std::vector<Texture*> mScores;

public:

	ScoreManager();
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

