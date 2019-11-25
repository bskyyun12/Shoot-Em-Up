#pragma once

#include "AnimatedTexture.h"
#include "Collider.h"
#include "BoxPiece.h"

class Box : public GameEntity
{
private:

	Timer* mTimer = nullptr;

	// box texture
	Texture* mBox = nullptr;
	AnimatedTexture* mBoxBreak = nullptr;

<<<<<<< HEAD
	BoxPiece* mBoxPieceUp = nullptr;
	BoxPiece* mBoxPieceDown = nullptr;
=======
	// bullet
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS] = { nullptr };
	float mFireTimer;
	float mFireRate;
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93

	// collider
	Collider* mCollider = nullptr;
	bool mGetDamage;
	bool mWasHit;

<<<<<<< HEAD
	bool hit = false;
	float mMoveSpeed;
	Timer* mTimer = nullptr;
=======
	int hp;
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93

public:

	Box(Vector2D pos);
	~Box();

	void Update();
	void Render();

};

