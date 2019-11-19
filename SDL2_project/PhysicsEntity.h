#pragma once
#include <vector>
#include "Collider.h"

class PhysicsEntity : public GameEntity
{
protected:
	// this opens an option to use multiple colliders on a single object(t.e. box collider for the head and circle collider for the body)
	std::vector<Collider*> mColliders;

public:

	PhysicsEntity();
	virtual ~PhysicsEntity();

	virtual void Render();

protected:

	bool ColliderCheck();

	void AddCollider(Collider* collider, Vector2D localPos = VECTOR2D_ZERO);
};

