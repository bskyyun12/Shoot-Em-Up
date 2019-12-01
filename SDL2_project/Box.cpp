#include "Box.h"
#include <iostream>
#include <random>
#include "ScoreBoard.h"

Box::Box(Vector2D pos)
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(Vector2D(64 / mBox->ScaledDimensions().x, 64 / mBox->ScaledDimensions().y)); // scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	// Explosion Texture
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

	// Impact texture
	mImpact = new AnimatedTexture("impact.png", 0, 0, 50, 50, 8, 0.1f, AnimatedTexture::horizontal);
	mImpact->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mImpact->Parent(this);
	mImpact->Rotate(180);
	mImpact->Translate(VECTOR2D_RIGHT * 40);
	impact = false;

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(Collider::TAG::enemyProjectile);
	}
	mFireTimer = 1.0f;
	mFireRate = 1.0f;

	// collider 
	mWasHit = false;
	AddCollider(new BoxCollider(Vector2D(mBox->ScaledDimensions().x * 0.7f, mBox->ScaledDimensions().y * 0.7f), Collider::TAG::enemy));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);

	mMoveYTimer = 0.0f;
	mMoveUp = true;
	mMoveSpeed = 100.0f;
	hp = 3;
	playOnce = true;


	Pos(pos);
}

Box::~Box()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	playOnce = false;

	// Textures
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

	delete mImpact;
	mImpact = nullptr;

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Box::Impact()
{
	impact = true;
}

void Box::Hit(PhysicsEntity* other)
{
	hp--;
	Impact();
	std::cout << "Box gets damage. Current hp is : " << hp << "." << std::endl;
	mBox->Active(true);
	mWasHit = true;
}

bool Box::IgnoreCollisions()
{
	return !Active();
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

		if (mWasHit)
		{
			mAudioManager->PlaySFX("Audios/laserHit.wav", 0, 4);
			mAudioManager->SFXVolume(4, 80);
			mWasHit = false;
		}

#pragma endregion Collision detection

		if (impact)
		{
			mImpact->Update();
		}

		if (mImpact->IsAnimationDone())
		{
			mImpact->ResetAnimationTimer();
			impact = false;
		}

		if (hp <= 0)
		{
			// death animation
			if (playOnce) // Ugly code but it works
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

			// move up and down
			mMoveYTimer += mTimer->DeltaTime();
			if (
				mMoveYTimer > 2.0f || 
				Pos().y <= ((int)ScoreBoard::GetScoreBoardHeight() + (int)(mBox->ScaledDimensions().y * 0.5f)) ||
				Pos().y >= (Graphics::Instance()->SCREEN_HEIGHT - (int)(mBox->ScaledDimensions().y * 0.5f))
				)
			{
				mMoveUp = !mMoveUp;
				mMoveYTimer = 0.0f;
			}

			if (mMoveUp)
				Translate(VECTOR2D_UP * (mMoveSpeed * 0.7f) * mTimer->DeltaTime());
			else
				Translate(VECTOR2D_DOWN * (mMoveSpeed * 0.7f) * mTimer->DeltaTime());

			
			if (Pos().x < 0)
			{
				std::random_device rd; // obtain a random number from hardware
				std::mt19937 eng(rd()); // seed the generator
				std::uniform_int_distribution<> distr((int)ScoreBoard::GetScoreBoardHeight() + (int)(mBox->ScaledDimensions().y * 0.5f), Graphics::Instance()->SCREEN_HEIGHT - (int)(mBox->ScaledDimensions().y * 0.5f)); // define the range

				float posX = (float)Graphics::Instance()->SCREEN_WIDTH;
				float ranY = (float)distr(eng); // get random widthin the range

				Pos(Vector2D(posX, ranY));
			}
		}
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

			// Debug colliderbox
			PhysicsEntity::Render();
		}
	}

	if (impact)
	{
		mImpact->Render();
	}
}