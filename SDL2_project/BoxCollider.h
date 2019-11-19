#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:

	// Box need 4 verts
	static const int MAX_VERTS = 4;

	// in this way, assigning mVert as a child of the box collider, when the box collider rotates, all the verts rotate with it
	GameEntity* mVerts[MAX_VERTS];

public:
	BoxCollider(Vector2D size);
	BoxCollider(Texture* objTex, std::string tag);
	~BoxCollider();

private:

	void AddVert(int index, Vector2D pos);

};

