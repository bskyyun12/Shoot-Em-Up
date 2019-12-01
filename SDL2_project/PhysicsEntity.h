#pragma once
#include "Collider.h"

class PhysicsEntity : public GameEntity
{
protected:

	unsigned long mId;

	std::vector<Collider*> mColliders;

	Collider::TAG mTag;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetId();

	Collider::TAG GetTag();

	bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	virtual void Render();

protected:

	virtual bool IgnoreCollisions();

	void AddCollider(Collider* collider, Vector2D localPos = VECTOR2D_ZERO);
	void RemoveCollider(Collider* collider);
};

