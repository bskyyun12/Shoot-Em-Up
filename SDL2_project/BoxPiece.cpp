#include "BoxPiece.h"

BoxPiece::BoxPiece(bool up)
{
	mUp = up;

	mMoveSpeed = 100.0f;
	mTimer = Timer::Instance();

	mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 38, 5, 12, 9, 4, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mBoxPieceTexture->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mBoxPieceTexture->Parent(this);

	// collider
	mCollider = Collider::Instance();
	mCollider->AddCollider(mBoxPieceTexture, Collider::TAG::enemy);
}

BoxPiece::~BoxPiece()
{
	delete mBoxPieceTexture;
	mBoxPieceTexture = nullptr;

	// collider
	mCollider = nullptr;
}

void BoxPiece::Update()
{
	if (mUp)
	{
		Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (!mUp)
	{
		Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime());
	}

	//Rotate(5);
}

void BoxPiece::Render()
{
	mBoxPieceTexture->Render();
}
