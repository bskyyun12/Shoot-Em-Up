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

	float mMoveSpeed;
	Timer* mTimer = nullptr;

	bool mUp;
	bool mRight;
	bool mDown;

public:

	BoxPiece(bool up, bool right, bool down);
	~BoxPiece();

	void Update();
	void Render();
};

