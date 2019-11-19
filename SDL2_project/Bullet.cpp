#include "Bullet.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mSpeed = 700.0f;

	mBullet = new AnimatedTexture("On (38x38).png", 0, 0, 38, 38, 8, 0.2f, AnimatedTexture::horizontal);
	mBullet->Scale(VECTOR2D_ONE * 0.7f);
	mBullet->Parent(this);
	mBullet->Pos(VECTOR2D_ZERO);
	//Rotate(-45); // bullet will be fired with -45 angle

	Reload();

	AddCollider(new BoxCollider(mBullet, "bullet"));
	//AddCollider(new BoxCollider(mBullet->ScaledDimensions()));
}

Bullet::~Bullet()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mBullet;
	mBullet = nullptr;
}

void Bullet::Fire(Vector2D pos)
{
	Pos(pos);
	Active(true);
	mAudioManager->PlaySFX("Audios/bullet.wav", 0, 1);
	mAudioManager->SFXVolume(1, 80);
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		PhysicsEntity::ColliderCheck();
		mBullet->Update();
		Translate(VECTOR2D_RIGHT * mSpeed * mTimer->DeltaTime(), local);

		Vector2D pos = Pos();
		if (pos.x < 0 || pos.x > Graphics::Instance()->SCREEN_WIDTH ||
			pos.y < 0 || pos.y > Graphics::Instance()->SCREEN_HEIGHT)
		{
			Reload();
		}
	}
}

void Bullet::Render()
{
	if (Active())
	{
		mBullet->Render();
		PhysicsEntity::Render();
	}
}
