#pragma once

#include "Formation.h"
#include "AnimatedTexture.h"
#include "BezierPath.h"

class Enemy : public GameEntity
{
public:

	enum STATES {flyIn, formation, dive, dead };

protected:
	static std::vector<std::vector<Vector2D>> sPaths;
	static Formation* sFormation;

	Timer* mTimer;

	Texture* mTexture;

	STATES mCurrentState;

	int mCurrentPath;
	
	int mCurrentWaypoint;
	const float EPSILON = 10.0f;

	float mSpeed;

	int mIndex;

	Vector2D mTargetPosition;

	bool mChallengeStage;

protected:

	virtual void PathComplete();

	virtual Vector2D FlyInTargetPosition();
	virtual void FlyInComplete();

	virtual Vector2D FormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	void HandleStates();

public:

	static void CreatePaths();
	static void SetFormation(Formation* f);


	Enemy(int index, int path, bool challengeStage);
	virtual ~Enemy();


	STATES CurrentState();

	void Update();

	void Render();
};
