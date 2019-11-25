#include "Box.h"
#include "AudioManager.h"

Box::Box(Vector2D pos)
{
	playOnce = true;
	mMoveSpeed = 100.0f;
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(Vector2D(64 / mBox->ScaledDimensions().x, 64 / mBox->ScaledDimensions().y)); // scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	mExplosion = new AnimatedTexture("explosion.png", 0, 0, 64, 64, 16, 1, AnimatedTexture::ANIM_DIR::horizontal);
	mExplosion->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mExplosion->Scale(VECTOR2D_ONE * 2);
	mExplosion->Parent(this);	// set mExplosion as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	// broken box pieces textures
	mBoxPieceUp = new BoxPiece(true, false, false);
	mBoxPieceUp->Parent(this);
	mBoxPieceRight = new BoxPiece(false, true, false);
	mBoxPieceRight->Parent(this);
	mBoxPieceDown = new BoxPiece(false, false, true);
	mBoxPieceDown->Parent(this);
	mBoxPieceDownRight = new BoxPiece(false, true, true);
	mBoxPieceDownRight->Parent(this);
	mBoxPieceUpRight = new BoxPiece(true, true, false);
	mBoxPieceUpRight->Parent(this);

	Pos(pos);

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(Collider::TAG::enemyProjectile);
	}
	mFireTimer = 1.0f;
	mFireRate = 1.0f;

	// collider 
	mCollider = Collider::Instance();
	mCollider->AddCollider(mBox, Collider::TAG::enemy);
	mWasHit = false;
	mGetDamage = false;

	hp = 3;
}

Box::~Box()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	playOnce = false;

	// collider
	mCollider->RemoveCollider(mBox);
	mCollider = nullptr;

	delete mBox;
	mBox = nullptr;

	delete mExplosion;
	mExplosion = nullptr;

	delete mBoxPieceUp;
	mBoxPieceUp = nullptr;

	delete mBoxPieceDown;
	mBoxPieceDown = nullptr;

	delete mBoxPieceRight;
	mBoxPieceRight = nullptr;

	delete mBoxPieceDownRight;
	mBoxPieceDownRight = nullptr;

	delete mBoxPieceUpRight;
	mBoxPieceUpRight = nullptr;

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Box::Update()
{
	if (Active())
	{
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
			mBox->Active(true);
		}

#pragma endregion Collision detection

		if (hp <= 0)
		{
			// death animation
			if (playOnce) // Ugly code
			{
				mAudioManager->PlaySFX("Audios/chunky_explosion.wav", 0, 3);
				mAudioManager->SFXVolume(3, 20);
				playOnce = false;
			}
			mBoxPieceUp->Update();
			mBoxPieceDown->Update();
			mBoxPieceRight->Update();
			mBoxPieceDownRight->Update();
			mBoxPieceUpRight->Update();
			mExplosion->Update();

			if (mExplosion->IsAnimationDone())
			{
				Active(false);
			}
		}
		else
		{
			Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime());

			if (Pos().x < 0)
				Pos(Vector2D(Graphics::Instance()->SCREEN_WIDTH, Pos().y));
		}
	}

	//if (mCollider->CollisionCheck(mBox, Collider::TAG::enemy))
	//{
	//	std::cout << "enemy needs to lose life!!" << std::endl;
	//}
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
		if (hp <= 0)
		{
			if (!mExplosion->IsAnimationDone())
			{
				mExplosion->Render();
			}
			mBoxPieceUp->Render();
			mBoxPieceDown->Render();
			mBoxPieceRight->Render();
			mBoxPieceDownRight->Render();
			mBoxPieceUpRight->Render();
		}
		else
		{
			mBox->Render();
		}
	}
}
