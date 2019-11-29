#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "BezierPath.h"
#include "PhysicsEntity.h"
#include "PhysicsManager.h"
#include "BoxCollider.h"

class Rocket : public PhysicsEntity
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
	Collider::TAG mTag;

public:

	Rocket(Collider::TAG tag);
	~Rocket();

	void CreatePath(Vector2D pos, int pathNum);
	void Reload();

	//collider
	void Hit(PhysicsEntity* other) override;

	void Update();
	void Render();

private:

	//collider
	bool IgnoreCollisions() override;
};

