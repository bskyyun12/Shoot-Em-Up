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

	BackgroundScroll();
	~BackgroundScroll();

	static bool mScroll;

	void AddBackground(std::string path, bool scroll = true);

	void ResetBackgroundPos(Texture* background);

	void Update();

	void Render();
};

