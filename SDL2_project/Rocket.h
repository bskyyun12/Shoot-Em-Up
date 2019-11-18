#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "BezierPath.h"

class Rocket : public GameEntity
{
private:

	static std::vector<std::vector<Vector2D>> sPaths;

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	float mSpeed;

	float midPoint;
	int mCurrentPath;
	int mCurrentWayPoint;
	const float EPSILON = 50.0f;

	AnimatedTexture* mRocket = nullptr;

public:

	Rocket();
	~Rocket();

	void CreatePath(Vector2D pos, int pathNum);
	void Reload();

	void Update();
	void Render();
};

