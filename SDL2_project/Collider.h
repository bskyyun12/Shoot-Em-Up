#pragma once
#include "Texture.h"
#include <vector>

class Collider : public GameEntity
{
public:

	enum TAG
	{
		player1,
		player2,
		enemy,
		player1Projectile,
		player2Projectile,
		enemyProjectile
	};

protected:

	TAG mTag;
	static const bool DEBUG_COLLIDERS = true;
	Texture* mDebugTexture = nullptr;

public:

	Collider(TAG tag);
	virtual ~Collider();

	virtual void Render();

protected:

	void SetDebugTexture(Texture* texture);
	TAG GetTag();

};