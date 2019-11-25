#pragma once

#include "AnimatedTexture.h"
#include "Collider.h"
#include "BoxPiece.h"

class Box : public GameEntity
{
private:

	// box texture
	Texture* mBox = nullptr;
	AnimatedTexture* mBoxBreak = nullptr;

	BoxPiece* mBoxPieceUp = nullptr;
	BoxPiece* mBoxPieceDown = nullptr;

	// collider
	Collider* mCollider = nullptr;

	bool hit = false;
	float mMoveSpeed;
	Timer* mTimer = nullptr;

public:

	Box();
	~Box();

	void Hit();

	void Update();
	void Render();

};

