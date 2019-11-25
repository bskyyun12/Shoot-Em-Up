#include "BoxPiece.h"

BoxPiece::BoxPiece(bool up, bool right, bool down)
{
	mUp = up;
	mRight = right;
	mDown = down;

	mMoveSpeed = 100.0f;
	mTimer = Timer::Instance();

	// mBoxPieceUpRight
	if (mUp && mRight)
	{
		mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 28, 0, 24, 24, 1, 1, AnimatedTexture::ANIM_DIR::horizontal);
	}
	// mBoxPieceDownRight
	else if (mDown && mRight)
	{
		mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 84, 0, 24, 24, 1, 1, AnimatedTexture::ANIM_DIR::horizontal);
	}
	// mBoxPieceRight
	else if (mRight)
	{
		mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 84, 0, 24, 24, 1, 1, AnimatedTexture::ANIM_DIR::horizontal);
	}
	// mBoxPieceUp
	else if (mUp)
	{
		mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 0, 0, 24, 24, 1, 1, AnimatedTexture::ANIM_DIR::horizontal);
	}
	// mBoxPieceDown
	else if (mDown)
	{
		mBoxPieceTexture = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 56, 0, 24, 24, 1, 1, AnimatedTexture::ANIM_DIR::horizontal);
	}

	mBoxPieceTexture->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mBoxPieceTexture->Parent(this);

	// collider
	//mCollider = Collider::Instance();
	//mCollider->AddCollider(mBoxPieceTexture, Collider::TAG::enemy);
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
	// mBoxPieceUpRight
	if (mUp && mRight)
	{
		Translate((VECTOR2D_RIGHT + VECTOR2D_UP) * mMoveSpeed * mTimer->DeltaTime());
	}
	// mBoxPieceDownRight
	else if (mDown && mRight)
	{
		Translate((VECTOR2D_RIGHT + VECTOR2D_DOWN) * mMoveSpeed * mTimer->DeltaTime());
	}
	// mBoxPieceRight
	else if (mRight)
	{
		Translate(VECTOR2D_RIGHT * 1.25f * mMoveSpeed * mTimer->DeltaTime());
	}
	// mBoxPieceUp
	else if (mUp)
	{
		Translate(VECTOR2D_UP * 0.75f * mMoveSpeed * mTimer->DeltaTime());
		Translate(VECTOR2D_RIGHT * 0.25f * mMoveSpeed * mTimer->DeltaTime());
	}
	// mBoxPieceDown
	else if (mDown)
	{
		Translate(VECTOR2D_DOWN * 0.75f * mMoveSpeed * mTimer->DeltaTime());
		Translate(VECTOR2D_RIGHT * 0.25f * mMoveSpeed * mTimer->DeltaTime());
	}
}

void BoxPiece::Render()
{
	mBoxPieceTexture->Render();
}
