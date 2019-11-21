#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Rocket.h"

class Box : public GameEntity
{
private:

	// box texture
	Texture* mBox = nullptr;
	Texture* mBoxBreak = nullptr;

	// collider
	Collider* mCollider = nullptr;

	bool hit = false;

public:

	Box();
	~Box();

	void Hit();

	void Update();
	void Render();

};

