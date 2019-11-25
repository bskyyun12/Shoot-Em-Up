#pragma once

#include "AnimatedTexture.h"
#include "Collider.h"
#include "Timer.h"

class BoxPiece : public GameEntity
{
private:

	// box piece texture
	AnimatedTexture* mBoxPieceTexture = nullptr;

	// collider
	Collider* mCollider = nullptr;

	bool hit = false;
	float mMoveSpeed;
	Timer* mTimer = nullptr;

	bool mUp;

public:

	BoxPiece(bool up);
	~BoxPiece();

	void Update();
	void Render();
};

