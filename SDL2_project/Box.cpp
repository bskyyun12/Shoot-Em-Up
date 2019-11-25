#include "Box.h"
#include "AudioManager.h"

Box::Box(Vector2D pos)
{
<<<<<<< HEAD
	hit = false;
	mMoveSpeed = 100.0f;
	mTimer = Timer::Instance();

=======
	mTimer = Timer::Instance();


>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(Vector2D(64 / mBox->ScaledDimensions().x, 64 / mBox->ScaledDimensions().y)); // scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	mBoxPieceUp = new BoxPiece(true);
	mBoxPieceUp->Parent(this);

	mBoxPieceDown = new BoxPiece(false);
	mBoxPieceDown->Parent(this);

	// box broken texture
<<<<<<< HEAD
	mBoxBreak = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 9, 7, 11, 9, 4, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mBoxBreak->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
=======
	mBoxBreak = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 0, 0, 28, 24, 4, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mBoxBreak->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mBoxBreak->Scale(Vector2D(64 / mBoxBreak->ScaledDimensions().x, 64 / mBoxBreak->ScaledDimensions().y)); // scale up to 64x64
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
	mBoxBreak->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	Pos(pos);

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(Collider::TAG::enemyProjectile);
	}
	mFireTimer = 0.5f;
	mFireRate = 0.5f;

	// collider 
	mCollider = Collider::Instance();
	mCollider->AddCollider(mBox, Collider::TAG::enemy);
	mWasHit = false;
	mGetDamage = false;

	hp = 5;

}

Box::~Box()
{
	mTimer = nullptr;

	delete mBox;
	mBox = nullptr;

	delete mBoxBreak;
	mBoxBreak = nullptr;

<<<<<<< HEAD
	delete mBoxPieceUp;
	mBoxPieceUp = nullptr;

	delete mBoxPieceDown;
	mBoxPieceDown = nullptr;

=======
	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93

	// collider
	mCollider = nullptr;
}

void Box::Update()
{
	if (Active())
	{
<<<<<<< HEAD
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
=======
		// bullet fire timer
		mFireTimer += mTimer->DeltaTime();
		if (mFireTimer > mFireRate)
		{
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (!mBullets[i]->Active() && hp > 0) // if hp is 0, it won't shoot
				{
					Vector2D pos = Pos();
					mBullets[i]->Fire(pos);
					break;
				}
			}
			mFireTimer = 0.0f;
		}

		// bullet shoot
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			mBullets[i]->Update();
		}

#pragma region Collision detection

		if (!mBox->Active())
		{
			hp--;
			std::cout << "Box gets damage. Current hp is : " << hp << "." << std::endl;
			AudioManager::Instance()->PlaySFX("Audios/chunky_explosion.wav");
			mBox->Active(true);
		}

#pragma endregion Collision detection

		if (hp <= 0)
		{
			// death animation
			mBoxBreak->Update();
			if (mBoxBreak->IsAnimationDone())
			{
				Active(false);
			}
		}
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
	}
}

void Box::Render()
{
	// bullet render
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}

	if (Active())
	{
<<<<<<< HEAD
		mBoxBreak->Render();
		mBoxPieceUp->Render();
		mBoxPieceDown->Render();
=======
		if (hp <= 0)
		{
			mBoxBreak->Render();
		}
		else
		{
			mBox->Render();
		}
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
	}
}
