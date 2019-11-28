#pragma once
#include "GameEntity.h"
#include "Timer.h"


class Formation : public GameEntity
{
private:
	Timer* mTimer;

	float mOffsetAmount;
	float mOffsetTimer;
	float mOffsetDelay;
	int mOffsetCounter;
	int mOffsetDirection;

	float mSpreadTimer;
	float mSpreadDelay;
	int mSpreadCounter;
	int mSpreadDirection;

	Vector2D mGridSize;

	bool mLocked;

public:
	Formation();
	~Formation();

	Vector2D GridSize();

	void Lock();

	void Update();
};


