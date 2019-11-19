#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

class BackgroundScroll : public GameEntity
{
private:

	// Timer
	Timer* mTimer = nullptr;

	// Background Variables
	Vector2D mBackgroundStartPos;
	Vector2D mBackgroundEndPos;
	float mScrollSpeed;

	// testing	
	std::vector<Texture*> mBackgrounds;
	Texture* mTempTex1 = nullptr;
	Texture* mTempTex2 = nullptr;

public:

	BackgroundScroll(std::string path, int backgroundAmount);
	~BackgroundScroll();

	static bool mScroll;

	void AddBackgroundImage(std::string path, bool scroll = true);
	void SetBackground(std::string path, int backgroundAmount);

	void ResetBackgroundPos(Texture* background);

	void Update();

	void Render();
};

