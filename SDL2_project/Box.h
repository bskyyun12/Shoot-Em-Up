#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Rocket.h"

class Box : public GameEntity
{
private:

	Timer* mTimer = nullptr;

	// box texture
	Texture* mBox = nullptr;
	AnimatedTexture* mBoxBreak = nullptr;

	// bullet
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS] = { nullptr };
	float mFireTimer;
	float mFireRate;

	// collider
	Collider* mCollider = nullptr;
	bool mGetDamage;
	bool mWasHit;

	int hp;

public:

	Box(Vector2D pos);
	~Box();

	void Update();
	void Render();

};

