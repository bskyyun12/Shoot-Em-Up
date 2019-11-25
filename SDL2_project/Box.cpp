#include "Box.h"
#include "AudioManager.h"

Box::Box()
{
	hit = false;
	mMoveSpeed = 100.0f;
	mTimer = Timer::Instance();

	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	mBoxPieceUp = new BoxPiece(true);
	mBoxPieceUp->Parent(this);

	mBoxPieceDown = new BoxPiece(false);
	mBoxPieceDown->Parent(this);

	// box broken texture
	mBoxBreak = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 9, 7, 11, 9, 4, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mBoxBreak->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mBoxBreak->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)
	
	// collider 
	mCollider = Collider::Instance();
	mCollider->AddCollider(mBox, Collider::TAG::enemy);
}

Box::~Box()
{
	delete mBox;
	mBox = nullptr;

	delete mBoxBreak;
	mBoxBreak = nullptr;

	delete mBoxPieceUp;
	mBoxPieceUp = nullptr;

	delete mBoxPieceDown;
	mBoxPieceDown = nullptr;


	// collider
	mCollider = nullptr;
}

void Box::Hit()
{
	hit = true;
	AudioManager::Instance()->PlaySFX("Audios/chunky_explosion.wav");
}

void Box::Update()
{
	if (Active())
	{
		Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime());
		hit = false;
	}
	else if (!(Active()))
	{
		Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		//Rotate(5);
		mBoxPieceUp->Update();
		mBoxPieceDown->Update();
	}
	
	//if (mCollider->CollisionCheck(mBox, Collider::TAG::enemy))
	//{
	//	std::cout << "enemy needs to lose life!!" << std::endl;
	//}
	

	if (!(Active()) && !hit)
	{
		Hit();
	}
}

void Box::Render()
{
	if (!hit)
	{
		mBox->Render();
	}
	else if (hit)
	{
		mBoxBreak->Render();
		mBoxPieceUp->Render();
		mBoxPieceDown->Render();
	}
}
