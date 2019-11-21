#include "Box.h"
#include "AudioManager.h"

Box::Box()
{
	hit = false;
	
	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	// box broken texture
	mBoxBreak = new Texture("Pixel Adventure/Items/Boxes/Box3/Break.png");
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
	//if (mCollider->CollisionCheck(mBox, Collider::TAG::enemy))
	//{
	//	std::cout << "enemy needs to lose life!!" << std::endl;
	//}

	//if (!mBox->Active())
	//{
	//	hit = true;
	//}
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
	}
}
