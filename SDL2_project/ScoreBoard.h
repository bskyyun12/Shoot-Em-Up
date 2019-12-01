#pragma once
#include "ScoreManager.h"

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

