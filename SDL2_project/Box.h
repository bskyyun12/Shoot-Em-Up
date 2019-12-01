#pragma once

#include "Bullet.h"
#include "BoxPiece.h"
#include "ScoreBoard.h"
#include "Player.h"
#include "Player2.h"
#include <random>

class Box : public PhysicsEntity
{
private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	// box texture
	Texture* mBox = nullptr;
	AnimatedTexture* mExplosion = nullptr;

	// broken box pieces textures
	BoxPiece* mBoxPieceUp = nullptr;
	BoxPiece* mBoxPieceDown = nullptr;
	BoxPiece* mBoxPieceDownRight = nullptr;
	BoxPiece* mBoxPieceUpRight = nullptr;
	BoxPiece* mBoxPieceRight = nullptr;

	// Impact
	AnimatedTexture* mImpact = nullptr;
	bool impact;

	// bullet
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS] = { nullptr };
	float mFireTimer;
	float mFireRate;

	// collider
	bool mWasHit;

	float mMoveYTimer;
	bool mMoveUp;
	float mMoveSpeed;
	int hp;
	bool playOnce;


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

