#include "Player2.h"
#include <iostream>

using std::cout;
using std::endl;

Player2::Player2()
{
	// handle movement
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mMoveSpeed = 500.0f;	// per second
	mBoundsOffset = 32.0f;	// half of player image's size

	// init current score and lives
	mScore = 0;
	mLives = 3;
	mScoreTimer = 0.5f;
	mScoreRate = 0.5f;

	// player texture
	mPlayer2 = new Texture("jumpBlue.png");
	mPlayer2->Scale(Vector2D(64.0f / mPlayer2->ScaledDimensions().x, 64.0f / mPlayer2->ScaledDimensions().y));	// scale up to 64x64
	mPlayer2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip2 = new AnimatedTexture("shipBlue.png", 32, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip2->Rotate(90);
	mPlayerShip2->Scale(Vector2D(64.0f / mPlayerShip2->ScaledDimensions().x, 96.0f / mPlayerShip2->ScaledDimensions().y));	// scale up to 64x96
	mPlayerShip2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)
	ship = false;

	// Impact texture
	mImpact = new AnimatedTexture("impact.png", 0, 0, 50, 50, 8, 0.1f, AnimatedTexture::horizontal);
	mImpact->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mImpact->Parent(this);
	mImpact->Translate(VECTOR2D_RIGHT * 60);
	impact = false;

	// Shield texture
	mShieldFront = new AnimatedTexture("shieldPurple.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldBack = new AnimatedTexture("shieldPurple.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldUp = new AnimatedTexture("shieldPurple.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldDown = new AnimatedTexture("shieldPurple.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldFront->Parent(this);
	mShieldBack->Parent(this);
	mShieldUp->Parent(this);
	mShieldDown->Parent(this);
	mShieldFront->Translate(VECTOR2D_RIGHT * 40);
	mShieldBack->Translate(VECTOR2D_LEFT * 40);
	mShieldBack->Rotate(180);
	mShieldUp->Translate(VECTOR2D_UP * 40);
	mShieldUp->Rotate(270);
	mShieldDown->Translate(VECTOR2D_DOWN * 40);
	mShieldDown->Rotate(90);
	shield = false;

	// Explosion Texture
	mExplosion = new AnimatedTexture("explosion.png", 0, 0, 64, 64, 16, 1, AnimatedTexture::ANIM_DIR::horizontal);
	mExplosion->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mExplosion->Scale(VECTOR2D_ONE * 3);
	mExplosion->Parent(this);	// set mExplosion as a child of this script(in this way, it's easier to change the box's transform in other scripts)
	exploded = false;
	playOnce = true;

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(Collider::TAG::player2Projectile);
	}
	mFireTimer = 0.5f;
	mFireRate = 0.5f;

	// rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		mRockets[i] = new Rocket(Collider::TAG::player2Projectile);
	}
	mRocketFireTimer = 2.0f;
	mRocketFireRate = 2.0f;

	// collider 	
	mShipColliders.insert(std::make_pair(new BoxCollider(Vector2D(50.0f, 20.0f), Collider::TAG::player1), Vector2D(10.0f, -20.0f)));
	mShipColliders.insert(std::make_pair(new BoxCollider(Vector2D(66.0f, 34.0f), Collider::TAG::player1), Vector2D(15.0f, 0.0f)));
	mShipColliders.insert(std::make_pair(new BoxCollider(Vector2D(50.0f, 20.0f), Collider::TAG::player1), Vector2D(10.0f, 20.0f)));

	mPlayerColliders.insert(std::make_pair(new BoxCollider(Vector2D(40.0f, 30.0f), Collider::TAG::player1), Vector2D(0.0f, -10.0f)));
	mPlayerColliders.insert(std::make_pair(new BoxCollider(Vector2D(35.0f, 34.0f), Collider::TAG::player1), Vector2D(0.0f, 15.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Player);

	mWasHit = false;

}

Player2::~Player2()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	// textures
	delete mPlayer2;
	mPlayer2 = nullptr;

	delete mPlayerShip2;
	mPlayerShip2 = nullptr;

	delete mImpact;
	mImpact = nullptr;

	// Shields
	delete mShieldFront;
	mShieldFront = nullptr;
	delete mShieldBack;
	mShieldBack = nullptr;
	delete mShieldUp;
	mShieldUp = nullptr;
	delete mShieldDown;
	mShieldDown = nullptr;

	delete mExplosion;
	mExplosion = nullptr;

	playOnce = false;

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}

	// rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		delete mRockets[i];
		mRockets[i] = nullptr;
	}

	// Collider
	mShipColliders.clear();
	mPlayerColliders.clear();
}

void Player2::HandleMovement()
{
	// save player's position before player moves
	Vector2D prevPlayerPos = Pos(local);

#pragma region Keyboard Input

	//if (!(mInputManager->JoysticksInitialiased()))
	//{
		if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// Fire Bullet
		if (mInputManager->KeyDown(SDL_SCANCODE_F) && !shield)
		{
			FireBullet();
		}

		// Fire Rocket
		if (mInputManager->KeyDown(SDL_SCANCODE_SPACE) && !shield)
		{
			FireRocket();
			AddScore(1);
		}

		// Raise Shield 
		if (mInputManager->KeyDown(SDL_SCANCODE_Q) && mScore > 0)
		{
			mShieldFront->Update();
			mShieldBack->Update();
			mShieldUp->Update();
			mShieldDown->Update();
			shield = true;
			RemoveScore(1);
		}

		// Lower Shield
		if (mInputManager->KeyReleased(SDL_SCANCODE_Q))
		{
			shield = false;
		}
	//}

#pragma endregion

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased() && mInputManager->GetNumberOfJoysticks() >= 2)
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(1, 1) > 0 || mInputManager->xValue(1, 1) < 0 ||
			mInputManager->yValue(1, 1) > 0 || mInputManager->yValue(1, 1) < 0)
		{
			Translate(Vector2D((float)mInputManager->xValue(1, 1), (float)mInputManager->yValue(1, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(1, 2) > 0 || mInputManager->xValue(1, 2) < 0 ||
			mInputManager->yValue(1, 2) > 0 || mInputManager->yValue(1, 2) < 0)
		{
			Translate(Vector2D((float)mInputManager->xValue(1, 2), (float)mInputManager->yValue(1, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		// Green (A) button
		if (InputManager::Instance()->GetButtonState(1, 0)) 
		{
			mPlayer2->Rotate(90);
		}

		// Red (B) button
		if (InputManager::Instance()->GetButtonState(1, 1)) 
		{

		}

		// Blue (X) button
		if (InputManager::Instance()->GetButtonState(1, 2)) 
		{
			FireBullet(); // Fire Bullet
		}

		// Yellow (Y) button
		if (InputManager::Instance()->GetButtonState(1, 3)) 
		{
			
		}

		// LB button
		if (InputManager::Instance()->GetButtonState(1, 4) && mScore > 0)
		{
			mShieldFront->Update();
			mShieldBack->Update();
			mShieldUp->Update();
			mShieldDown->Update();
			shield = true;		// Raise Shield
			RemoveScore(1);
		}

		// Released LB button
		if (!(InputManager::Instance()->GetButtonState(1, 4)) && 
			shield && !(mInputManager->KeyDown(SDL_SCANCODE_Q)))
		{
			shield = false;		// Lower Shield
		}

		// RB button
		if (InputManager::Instance()->GetButtonState(1, 5)) 
		{
			FireRocket(); // Fire Rocket
		}

		// Back/Select button
		if (InputManager::Instance()->GetButtonState(1, 6)) 
		{

		}

		// Start button
		if (InputManager::Instance()->GetButtonState(1, 7)) 
		{

		}

		// Left Stick button
		if (InputManager::Instance()->GetButtonState(1, 8)) 
		{

		}

		// Right Stick button
		if (InputManager::Instance()->GetButtonState(1, 9)) 
		{

		}

		// XBOX button
		if (InputManager::Instance()->GetButtonState(1, 10)) 
		{
	
		}

#pragma endregion

	}

#pragma endregion

	// Set Player Move Bounds
	if (
		Pos().x < mBoundsOffset ||
		Pos().x > Graphics::Instance()->SCREEN_WIDTH - mBoundsOffset ||
		Pos().y < mBoundsOffset + 90.0f ||
		Pos().y > Graphics::Instance()->SCREEN_HEIGHT - mBoundsOffset
		)
	{
		Pos(prevPlayerPos);	// set position back to previous position
	}
}

void Player2::FireBullet()
{
	if (mFireTimer > mFireRate)
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				Vector2D pos = Pos();
				mBullets[i]->Fire(pos);
				break;
			}
		}
		mFireTimer = 0.0f;
	}
}

void Player2::FireRocket()
{
	if (mRocketFireTimer > mRocketFireRate)
	{
		// rocket
		for (int i = 0; i < MAX_ROCKETS; i++)
		{
			if (!mRockets[i]->Active())
			{
				Vector2D pos = Pos();
				mRockets[i]->CreatePath(pos, i+2);
			}
		}
		mRocketFireTimer = 0.0f;
	}
}

unsigned int Player2::Score()
{
	return mScore;
}

int Player2::Lives()
{
	return mLives;
}

void Player2::AddScore(unsigned int score)
{
	if (mScoreTimer > mScoreRate)
	{
		mScore += score;
		mScoreTimer = 0.0f;
	}
}

void Player2::RemoveScore(unsigned int score)
{
	if (mScoreTimer > mScoreRate)
	{
		mScore -= score;
		if (mScore <= 0)
		{
			shield = false;
		}
	}
}

void Player2::ToggleTexture()
{
	ship = !ship;

	if (ship)
	{
		for (auto col : mPlayerColliders)
			RemoveCollider(col.first);

		for (auto col : mShipColliders)
			AddCollider(col.first, col.second);
	}
	else
	{
		for (auto col : mShipColliders)
			RemoveCollider(col.first);

		for (auto col : mPlayerColliders)
			AddCollider(col.first, col.second);
	}
}

void Player2::Impact()
{
	impact = true;
}

void Player2::Explode()
{
	exploded = true;
}

void Player2::AddHealth()
{
	mLives++;
}

void Player2::RemoveHealth()
{
	mLives--;
}

void Player2::Hit(PhysicsEntity* other)
{
	std::cout << "Player2 got hit." << std::endl;
	mWasHit = true;
	Impact();
	if (!shield)
	{
		RemoveHealth();
		if (mLives <= 0)
		{
			exploded = true;
		}
	}
}

bool Player2::IgnoreCollisions()
{
	return !Active();
}

void Player2::Update()
{
	mFireTimer += mTimer->DeltaTime();
	mRocketFireTimer += mTimer->DeltaTime();
	mScoreTimer += mTimer->DeltaTime();

	// player won't do anything during stage preparation
	if (Active())
	{
		if (mWasHit)
			mWasHit = false;

		HandleMovement();

		AddScore(1);

		if (impact && !exploded)
		{
			mImpact->Update();
			mAudioManager->PlaySFX("Audios/laserHit.wav", 0, 4);
			mAudioManager->SFXVolume(4, 80);
		}

		if (mImpact->IsAnimationDone())
		{
			mImpact->ResetAnimationTimer();
			impact = false;
		}
	}

	// exploded
	if (exploded)
	{
		if (playOnce) // Ugly code but it works
		{
			mAudioManager->PlaySFX("Audios/chunky_explosion.wav", 0, 3);
			mAudioManager->SFXVolume(3, 20);
			playOnce = false;
		}
		mExplosion->Update();
		if (mExplosion->IsAnimationDone())
		{
			Active(false);
		}
	}

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}

	// Rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		mRockets[i]->Update();
	}
}

void Player2::Render()
{
	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}

	// Rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		mRockets[i]->Render();
	}

	if (exploded)
	{
		if (!mExplosion->IsAnimationDone())
		{
			mExplosion->Render();
		}
	}
	else if (!ship)
	{
		mPlayer2->Render();
	}
	else if (ship)
	{
		mPlayerShip2->Render();
	}

	if (impact && !exploded)
	{
		mImpact->Render();
	}

	if (shield)
	{
		mShieldFront->Render();
		mShieldBack->Render();
		mShieldUp->Render();
		mShieldDown->Render();
	}

	// Debug colliderbox
	PhysicsEntity::Render();
}
