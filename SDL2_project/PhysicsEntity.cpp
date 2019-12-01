#include "PhysicsEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"
#include <iostream>

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

Collider::TAG PhysicsEntity::GetTag()
{
	return mTag;
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
	mTag = collider->GetTag();

	std::vector<Collider*>::iterator it;
	it = std::find(mColliders.begin(), mColliders.end(), collider);

	// not found
	if (it == mColliders.end())
	{
		collider->Parent(this);
		collider->Pos(localPos);

		mColliders.push_back(collider);
	}
	else
	{
		std::cout << "AddCollider fail - already exists." << std::endl;
	}
}

void PhysicsEntity::RemoveCollider(Collider* collider)
{
	std::vector<Collider*>::iterator it;
	it = std::find(mColliders.begin(), mColliders.end(), collider);

	// found
	if (it != mColliders.end())
	{
		mColliders.erase(it);
	}
	else
	{
		std::cout << "RemoveCollider fail - doesn't exists." << std::endl;
	}
}

void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}
}
