#pragma once

#include "AnimatedTexture.h"
#include "BoxPiece.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

class Box : public PhysicsEntity
{
private:

	Timer* mTimer = nullptr;
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
	bool mWasHit;

	float mMoveSpeed;
	int hp;
	bool playOnce;

	// Impact
	AnimatedTexture* mImpact = nullptr;
	bool impact;

public:

	Box(Vector2D pos);
	~Box();

	void Impact();

	// collider
	void Hit(PhysicsEntity* other) override;

	void Update();
	void Render();


private:

	// collider
	bool IgnoreCollisions() override;

};

