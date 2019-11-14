#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

class BackgroundScroll : public GameEntity
{
private:

	// Timer
	Timer* mTimer = nullptr;

	// Background Variables
	float mBackgroundImageWidth;
	float mBackgroundImageHeight;
	Vector2D mBackgroundStartPos;
	Vector2D mBackgroundEndPos;
	float mScrollSpeed;

	// Background Entities
	Texture* mBackground_1 = nullptr;
	Texture* mBackground_2 = nullptr;
	Texture* mBackground_2_1 = nullptr;
	Texture* mBackground_3 = nullptr;
	Texture* mBackground_3_1 = nullptr;
	Texture* mBackground_4 = nullptr;
	Texture* mBackground_4_1 = nullptr;
	Texture* mBackground_5 = nullptr;
	Texture* mBackground_5_1 = nullptr;

public:

	BackgroundScroll();
	~BackgroundScroll();

	static bool mScroll;

	void ResetBackgroundPos(Texture* background);

	void Update();

	void Render();
};

