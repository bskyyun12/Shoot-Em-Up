#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2D size, TAG tag) : Collider(tag)
{
	AddVert(0, Vector2D(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2D(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2D(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2D(0.5f * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVert[i];
		mVert[i] = nullptr;
	}
}

Vector2D BoxCollider::GetVertexPos(int index)
{
	return mVert[index]->Pos();
}

void BoxCollider::AddVert(int index, Vector2D pos)
{
	mVert[index] = new GameEntity(pos);
	mVert[index]->Parent(this);
}
