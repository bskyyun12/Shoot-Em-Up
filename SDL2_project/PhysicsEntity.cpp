#include "PhysicsEntity.h"
#include <iostream>

PhysicsEntity::PhysicsEntity()
{
}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();
}

bool PhysicsEntity::ColliderCheck()
{
	//std::cout << "ColliderCheck start " << std::endl;
	//std::cout << "mColliders.size() : " << mColliders.size() << std::endl;

	for (int i = 0; i < mColliders.size(); i++)
	{
		//std::cout << "mColliders[i]->GetTag() : " << mColliders[i]->GetTag() << std::endl;

		//for (int j = 0; j < mColliders.size(); j++)
		//{
		//	std::cout << "mColliders[i]->GetTag() : " << mColliders[i]->GetTag() << std::endl;
		//	if (mColliders[i]->GetTag() != mColliders[j]->GetTag())
		//	{
		//		if (SDL_HasIntersection(&mColliders[i]->GetRect(), &mColliders[j]->GetRect()))
		//		{
		//			std::cout << mColliders[i]->GetTag() << "hits : " << mColliders[j]->GetTag() << std::endl;
		//			return true;
		//		}
		//	}
		//}
	}
	return false;
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2D localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);

	mColliders.push_back(collider);

	std::cout << "collider->GetTag() : " << collider->GetTag() << std::endl;
	std::cout << "mColliders.size() : " << mColliders.size() << std::endl;

}


void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}
}