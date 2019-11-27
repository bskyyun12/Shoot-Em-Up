#pragma once

#include "AnimatedTexture.h"
#include "Collider.h"
#include "BoxPiece.h"
#include "Bullet.h"
#include "AudioManager.h"

class Box : public GameEntity
{
private:

	AudioManager* mAudioManager = nullptr;

	// box texture
	Texture* mBox = nullptr;
	AnimatedTexture* mExplosion = nullptr;

	BoxPiece* mBoxPieceUp = nullptr;
	BoxPiece* mBoxPieceDown = nullptr;
	BoxPiece* mBoxPieceDownRight = nullptr;
	BoxPiece* mBoxPieceUpRight = nullptr;
	BoxPiece* mBoxPieceRight = nullptr;

	// bullet
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS] = { nullptr };
	float mFireTimer;
	float mFireRate;

	// collider
	Collider* mCollider = nullptr;
	bool mGetDamage;
	bool mWasHit;

	bool hit = false;
	float mMoveSpeed;
	Timer* mTimer = nullptr;

	int hp;
	bool playOnce;

	// Impact
	AnimatedTexture* mImpact = nullptr;
	bool impact;

public:

	Box(Vector2D pos);
	~Box();

	void Impact();

	void Update();
	void Render();

};

