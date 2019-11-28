#include "Formation.h"

Formation::Formation()
{
	mTimer = Timer::Instance();

	mOffsetAmount = 30.0f;
	mOffsetDelay = 1.0f;
	mOffsetTimer = 0.0f;
	mOffsetCounter = 4;
	mOffsetDirection = 1;


	mSpreadTimer = 0.0f;
	mSpreadDelay = 1.0f;
	mSpreadCounter = 0;
	mSpreadDirection = 1;

	mLocked = false;

	mGridSize = Vector2D(40.0f, 20.0f);
}

Formation::~Formation()
{
	mTimer = NULL;
}
Vector2D Formation::GridSize()
{
	return mGridSize;
}

void Formation::Lock()
{
	mLocked = true;
}

void Formation::Update()
{
	if (!mLocked || mOffsetCounter != 4)
	{
		mOffsetTimer += mTimer->DeltaTime();
		if (mOffsetTimer >= mOffsetDelay)
		{
			mOffsetCounter++;
			Translate(VECTOR2D_UP * mOffsetDirection * mOffsetAmount, world);

			if (mOffsetCounter == 8)
			{
				mOffsetCounter = 0;
				mOffsetDirection *= -1;
			}

			mOffsetTimer = 0.0f;
		}
	}
}