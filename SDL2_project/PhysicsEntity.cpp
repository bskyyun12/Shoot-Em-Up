#include "PhysicsEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"

PhysicsEntity::PhysicsEntity()
{
	mId = 0;
}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();

	if (mId != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}

unsigned long PhysicsEntity::GetId()
{
	return mId;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
		return false;

	for (int i = 0; i < mColliders.size(); i++)
	{
		for (int j = 0; j < other->mColliders.size(); j++)
		{
			if (ColliderColliderCheck(mColliders[i], other->mColliders[j]))
			{
				return true;
			}
		}
	}
	return false;
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{
}

bool PhysicsEntity::IgnoreCollisions()
{
	return false;
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2D localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);

	mColliders.push_back(collider);
}

void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}
}
