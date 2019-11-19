#include "Collider.h"

Collider::Collider(ColliderType type)
{
	mType = type;
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


SDL_Rect Collider::GetRect()
{
	return mCollider;
}

std::string Collider::GetTag()
{
	return mTag;
}

void Collider::Render()
{
	if (mDebugTexture)
	{
		mDebugTexture->Render();
	}
}