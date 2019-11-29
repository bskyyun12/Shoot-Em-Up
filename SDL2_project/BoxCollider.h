#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:
	static const int MAX_VERTS = 4;

	GameEntity* mVert[MAX_VERTS];

public:
	BoxCollider(Vector2D size, TAG tag);
	~BoxCollider();

	Vector2D GetVertexPos(int index);

private:

	void AddVert(int index, Vector2D pos);
};

