#include "Box.h"
#include "AudioManager.h"

Box::Box(Vector2D pos)
{
	mTimer = Timer::Instance();


	// box texture
	mBox = new Texture("Pixel Adventure/Items/Boxes/Box3/Idle.png");
	mBox->Scale(Vector2D(64 / mBox->ScaledDimensions().x, 64 / mBox->ScaledDimensions().y)); // scale up to 64x64
	mBox->Parent(this);	// set mBox as a child of this script(in this way, it's easier to change the box's transform in other scripts)

	// box broken texture
	mBoxBreak = new AnimatedTexture("Pixel Adventure/Items/Boxes/Box3/Break.png", 0, 0, 28, 24, 4, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mBoxBreak->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mBoxBreak->Scale(Vector2D(64 / mBoxBreak->ScaledDimensions().x, 64 / mBoxBreak->ScaledDimensions().y)); // scale up to 64x64
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

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}

	// collider
	mCollider = nullptr;
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
			mBoxBreak->Render();
		}
		else
		{
			mBox->Render();
		}
	}
}
