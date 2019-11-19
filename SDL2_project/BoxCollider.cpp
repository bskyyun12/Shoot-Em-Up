#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2D size) : Collider(ColliderType::Box)
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

BoxCollider::BoxCollider(Texture* objTex, std::string tag) : Collider(ColliderType::Box)
{
	mCollider.x = objTex->Pos().x;
	mCollider.y = objTex->Pos().y;
	mCollider.x = objTex->ScaledDimensions().x;
	mCollider.y = objTex->ScaledDimensions().y;

	mTag = tag;

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->Scale(objTex->ScaledDimensions() / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

void BoxCollider::AddVert(int index, Vector2D pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}
