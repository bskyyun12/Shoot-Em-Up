#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "BezierPath.h"
#include "Collider.h"

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

	//collider 
	Collider* mCollider = nullptr;

public:

	Rocket(Collider::TAG tag);
	~Rocket();

	void CreatePath(Vector2D pos, int pathNum);
	void Reload();

	void Update();
	void Render();
};

