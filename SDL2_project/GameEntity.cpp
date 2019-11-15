#include "GameEntity.h"

GameEntity::GameEntity(Vector2D pos) {

	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
	mScale = VECTOR2D_ONE;
}

GameEntity::~GameEntity()
{
	mParent = nullptr;
}

void GameEntity::Pos(Vector2D pos)
{
	mPos = pos;
}

Vector2D GameEntity::Pos(SPACE space)
{
	if (space == local || mParent == NULL)
		return mPos;

	Vector2D parentScale = mParent->Scale(world);

	//The object's local position is rotated by the parent's rotation
	//The final position also depends on the parent's scale (if the parent is scaled up, the object should be further away from the parent)
	Vector2D childPos = Vector2D(mPos.x * parentScale.x, mPos.y * parentScale.y);
	Vector2D rotPos = RotateVector(childPos, mParent->Rotation(local));

	return mParent->Pos(world) + rotPos;
}

void GameEntity::Rotation(float rotation)
{
	mRotation = rotation;

	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;

	// I don't get this. why?
	//if (mRotation > 360.0f) {

	//	int mul = mRotation / 360;
	//	mRotation -= 360.0f * mul;

	//}
	//else if (mRotation < 0.0f) {

	//	int mul = (mRotation / 360) - 1;
	//	mRotation -= 360.0f * mul;
	//}
}

float GameEntity::Rotation(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void GameEntity::Scale(Vector2D scale) 
{
	mScale = scale;
}

Vector2D GameEntity::Scale(SPACE space) 
{
	if (space == local || mParent == nullptr)
		return mScale;

	Vector2D scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::Active()
{
	return mActive;
}

void GameEntity::Parent(GameEntity* parent)
{
	//If the parent is removed, The Position/Rotation/Scale are the GameEntity's world values, to keep the object looking the same after the removal of the parent;
	if (parent == nullptr) 
	{
		mPos = Pos(world);
		mScale = Scale(world);
		mRotation = Rotation(world);
	}
	else
	{
		//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
		if (mParent != NULL)
			Parent(NULL);

		Vector2D parentScale = parent->Scale(world);

		//Setting the local position to be relative to the new parent (while maintaining the same world position as before)
		Vector2D distance = Pos(world) - parent->Pos(world);
		mPos = RotateVector(distance, -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		//Setting the local rotation to be relative to the new parent (while maintaining the same world rotation as before)
		mRotation = mRotation - parent->Rotation(world);

		//Setting the new scale to be relative to the new parent (while maintaining the same world scale as before)
		mScale = Vector2D(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameEntity* GameEntity::Parent()
{
	return mParent;
}

void GameEntity::Translate(Vector2D vec, SPACE space)
{
	if (space == world)
	{
		mPos += vec;
	}
	else
	{
		mPos += RotateVector(vec, Rotation());
	}
}

void GameEntity::Rotate(float amount) 
{
	mRotation += amount;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}
