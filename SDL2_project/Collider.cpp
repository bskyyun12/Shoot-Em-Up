#include "Collider.h"

Collider::Collider(TAG tag) : mTag(tag)
{
	mDebugTexture = nullptr;
}

Collider::~Collider()
{
	if (mDebugTexture)
	{
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
}

void Collider::SetDebugTexture(Texture* texture)
{
	delete mDebugTexture;
	mDebugTexture = texture;
	mDebugTexture->Parent(this);
}

Collider::TAG Collider::GetTag()
{
	return mTag;
}

void Collider::Render()
{
	if (DEBUG_COLLIDERS)
	{
		mDebugTexture->Render();
	}
}