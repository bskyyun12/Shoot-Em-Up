#pragma warning( push )
#pragma warning (disable : 4244 )

#include "Enemy.h"

std::vector<std::vector<Vector2D>> Enemy::sPaths;
Formation* Enemy::sFormation = NULL;

void Enemy::CreatePaths()
{



	int currentPath = 0;
	BezierPath* path = new BezierPath();
	path->AddCurve({ Vector2D(1500.0F, 400.0F) /*Change starting postion of enemy! */, Vector2D(350.0F, -250.0F ), Vector2D(700.0F, 1310.0F), Vector2D(1350.0F, 50.0F) }, 30); // End position of enemy

	sPaths.push_back(std::vector<Vector2D>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

void Enemy::SetFormation(Formation* f)
{
	sFormation = f;
}

Enemy::Enemy(int index, int path, bool challengeStage)
{
	mTimer = Timer::Instance();

	mCurrentPath = path;
	mCurrentState = flyIn;

	mCurrentWaypoint = 1;
	Pos(sPaths[mCurrentPath][0]);

	mTexture = NULL;

	mSpeed = 400.0f;

	mIndex = index;

	mChallengeStage = challengeStage;
}

Enemy::~Enemy()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Enemy::PathComplete()
{
	if (mChallengeStage)
	{
		mCurrentState = dead;
	}
}

Vector2D Enemy::FlyInTargetPosition()
{
	return sFormation->Pos() + mTargetPosition;
}

void Enemy::FlyInComplete()
{
	Pos(FlyInTargetPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = formation;
}

void Enemy::HandleFlyInState()
{

	if (mCurrentWaypoint < sPaths[mCurrentPath].size())
	{
		Vector2D dist = sPaths[mCurrentPath][mCurrentWaypoint] - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.x, dist.y) * RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWaypoint] - Pos()).MagnitudeSqr() < EPSILON)
			mCurrentWaypoint++;

		if (mCurrentWaypoint >= sPaths[mCurrentPath].size())
		{
			PathComplete();
		}
	}
	else
	{
		Vector2D dist = FlyInTargetPosition() - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.x, dist.y) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON)
		{
			FlyInComplete();
		}
	}

}

void Enemy::HandleFormationState()
{
	Pos(FormationPosition());
}


void Enemy::HandleStates()
{
	switch (mCurrentState)
	{
	case flyIn:
		HandleFlyInState();
		break;
	case formation:
		HandleFormationState();
		break;
	case dive:
		HandleDiveState();
		break;
	case dead:
		HandleDeadState();
		break;
	default:
		break;
	}
}

Enemy::STATES Enemy::CurrentState()
{
	return mCurrentState;
}

void Enemy::Update()
{
	if (Active())
	{
		HandleStates();
	}
}

void Enemy::Render()
{
	if (Active())
	{
		mTexture->Render();

		for (int i = 0; i < sPaths[mCurrentPath].size() -1; i++)
		{
			//Graphics::Instance()->DrawLine(sPaths[mCurrentPath][i].x, sPaths[mCurrentPath][i].y, sPaths[mCurrentPath][i + 1].x, sPaths[mCurrentPath][i + 1].y);
		}
	}
}

#pragma warning( pop )