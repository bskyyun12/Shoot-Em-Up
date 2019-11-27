#include "Bullet.h"

Bullet::Bullet(Collider::TAG tag)
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mSpeed = 700.0f;
	switch (tag)
	{
	case Collider::player1Projectile:
		mBullet = new AnimatedTexture("laserRed.png", 0, 0, 50, 16, 9, 0.5f, AnimatedTexture::horizontal);
		break;
	case Collider::player2Projectile:
		mBullet = new AnimatedTexture("laserBlue.png", 0, 0, 50, 16, 9, 0.5f, AnimatedTexture::horizontal);
		break;
	case Collider::enemyProjectile:
		mBullet = new AnimatedTexture("plasmaCyan.png", 0, 0, 70, 65, 9, 0.5f, AnimatedTexture::horizontal);
		break;
	default:
		break;
	}
	mBullet->Scale(Vector2D(32 / mBullet->ScaledDimensions().x, 32 / mBullet->ScaledDimensions().y));
	mBullet->Parent(this);
	mBullet->Pos(VECTOR2D_ZERO);
	//Rotate(-45); // bullet will be fired with -45 angle

	mBullet->Active(false);
	Reload();

	//collider
	mCollider = Collider::Instance();
	mCollider->AddCollider(mBullet, tag);
	mTag = tag;

}

Bullet::~Bullet()
{
	mTimer = nullptr;
	mAudioManager = nullptr;

	// collider
	mCollider->RemoveCollider(mBullet);
	mCollider = nullptr;

	delete mBullet;
	mBullet = nullptr;
}

void Bullet::Fire(Vector2D pos)
{
	Pos(pos);
	Active(true);
	mBullet->Active(true);
	mAudioManager->PlaySFX("Audios/bullet.wav", 0, 1);
	mAudioManager->SFXVolume(1, 80);
}

void Bullet::Reload()
{
	Pos(VECTOR2D_ONE * -100.0f);
	Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		mBullet->Update();

		if (mTag == Collider::TAG::player1Projectile || mTag == Collider::TAG::player2Projectile)
			Translate(VECTOR2D_RIGHT * mSpeed * mTimer->DeltaTime(), local);
		else
			Translate(VECTOR2D_LEFT * mSpeed * mTimer->DeltaTime(), local);

		Vector2D pos = Pos();
		if (pos.x < 0 || pos.x > Graphics::Instance()->SCREEN_WIDTH ||
			pos.y < 0 || pos.y > Graphics::Instance()->SCREEN_HEIGHT)
		{
			Reload();
		}

		if (!mBullet->Active())
		{
			Reload();
		}

	}
}

void Bullet::Render()
{
	//if (active())
	//{
	//	mbullet->render();
	//}

	mBullet->Render();
}
