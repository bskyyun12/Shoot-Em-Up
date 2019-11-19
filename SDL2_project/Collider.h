#pragma once
#include "Texture.h" // debug purpose
#include <vector>

class Collider : public GameEntity
{
public:

	enum class ColliderType 
	{
		Box,
		Circle
	};

protected:

	ColliderType mType;

	static const bool DEBUG_COLLIDERS = true;
	Texture* mDebugTexture = nullptr;

	SDL_Rect mCollider;
	std::string mTag;

	// testing

public:

	Collider(ColliderType type);
	virtual ~Collider();

	SDL_Rect GetRect();
	std::string GetTag();
	virtual void Render();

protected:

	void SetDebugTexture(Texture* texture);

};

