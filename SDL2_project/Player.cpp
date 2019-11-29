#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player()
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
	mPlayer = new Texture("jumpOrange.png");
	mPlayer->Scale(Vector2D(64.0f / mPlayer->ScaledDimensions().x, 64.0f / mPlayer->ScaledDimensions().y));	// scale up to 64x64
	mPlayer->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip = new AnimatedTexture("shipRed.png", 32, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip->Scale(Vector2D(64.0f / mPlayerShip->ScaledDimensions().x, 96.0f / mPlayerShip->ScaledDimensions().y));	// scale up to 64x96
	mPlayerShip->Rotate(90);
	mPlayerShip->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)
	ship = false;

	// Impact texture
	mImpact = new AnimatedTexture("impact.png", 0, 0, 50, 50, 8, 0.1f, AnimatedTexture::horizontal);
	mImpact->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mImpact->Parent(this);
	mImpact->Translate(VECTOR2D_RIGHT * 60);
	impact = false;

	// Shield texture
	mShieldFront = new AnimatedTexture("shieldBlue.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldBack = new AnimatedTexture("shieldBlue.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldUp = new AnimatedTexture("shieldBlue.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShieldDown = new AnimatedTexture("shieldBlue.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
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
		mBullets[i] = new Bullet(Collider::TAG::player1Projectile);
	}
	mFireTimer = 0.5f;
	mFireRate = 0.5f;

	// rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		mRockets[i] = new Rocket(Collider::TAG::player1Projectile);
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

Player::~Player()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	// textures
	delete mPlayer;
	mPlayer = nullptr;

	delete mPlayerShip;
	mPlayerShip = nullptr;

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

void Player::HandleMovement()
{
	// save player's position before player moves
	Vector2D prevPlayerPos = Pos(local);

#pragma region Keyboard Input

	//if (!(mInputManager->JoysticksInitialiased()))
	//{
		if (mInputManager->KeyDown(SDL_SCANCODE_RIGHT))
		{
			Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_LEFT))
		{
			Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_UP))
		{
			Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_DOWN))
		{
			Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// Fire Bullet
		if (mInputManager->KeyDown(SDL_SCANCODE_RCTRL) && !shield)
		{
			FireBullet();
		}

		// Fire Rocket
		if (mInputManager->KeyDown(SDL_SCANCODE_RETURN) && !shield)
		{
			FireRocket();
		}

		// Raise Shield 
		if (mInputManager->KeyDown(SDL_SCANCODE_BACKSPACE) && mScore > 0)
		{
			mShieldFront->Update();
			mShieldBack->Update();
			mShieldUp->Update();
			mShieldDown->Update();
			shield = true;
			RemoveScore(1);
		}

		// Lower Shield
		if (mInputManager->KeyReleased(SDL_SCANCODE_BACKSPACE))
		{
			shield = false;
		}
	//}

#pragma endregion

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased())
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(0, 1) > 0 || mInputManager->xValue(0, 1) < 0 ||
			mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 1) < 0)
		{
			Translate(Vector2D((float)mInputManager->xValue(0, 1), (float)mInputManager->yValue(0, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(0, 2) > 0 || mInputManager->xValue(0, 2) < 0 ||
			mInputManager->yValue(0, 2) > 0 || mInputManager->yValue(0, 2) < 0)
		{
			Translate(Vector2D((float)mInputManager->xValue(0, 2), (float)mInputManager->yValue(0, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		// Green (A) button
		if (InputManager::Instance()->GetButtonState(0, 0)) 
		{
			mPlayer->Rotate(90);
		}

		// Red (B) button
		if (InputManager::Instance()->GetButtonState(0, 1)) 
		{

		}

		// Blue (X) button
		if (InputManager::Instance()->GetButtonState(0, 2) && !shield) 
		{
			FireBullet(); // Fire bullet
		}

		// Yellow (Y) button
		if (InputManager::Instance()->GetButtonState(0, 3)) 
		{

		}

		// LB button
		if (InputManager::Instance()->GetButtonState(0, 4) && mScore > 0) 
		{
			mShieldFront->Update();
			mShieldBack->Update();
			mShieldUp->Update();
			mShieldDown->Update();
			shield = true;		// Raise Shield
			RemoveScore(1);
		}

		// Released LB button
		if (!(InputManager::Instance()->GetButtonState(0, 4)) && 
			shield && !(mInputManager->KeyDown(SDL_SCANCODE_BACKSPACE)))
		{
			shield = false;		// Lower Shield
		}

		// RB button
		if (InputManager::Instance()->GetButtonState(0, 5) && !shield) 
		{
			FireRocket();		// Fire Rocket
		}

		// Back/Select button
		if (InputManager::Instance()->GetButtonState(0, 6)) 
		{

		}

		// Start button
		if (InputManager::Instance()->GetButtonState(0, 7)) 
		{

		}

		// Left Stick button
		if (InputManager::Instance()->GetButtonState(0, 8)) 
		{

		}

		// Right Stick button
		if (InputManager::Instance()->GetButtonState(0, 9)) 
		{

		}

		// XBOX button
		if (InputManager::Instance()->GetButtonState(0, 10)) 
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

void Player::FireBullet()
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

void Player::FireRocket()
{
	if (mRocketFireTimer > mRocketFireRate)
	{
		// rocket
		for (int i = 0; i < MAX_ROCKETS; i++)
		{
			if (!mRockets[i]->Active())
			{
				Vector2D pos = Pos();
				mRockets[i]->CreatePath(pos, i);
			}
		}
		mRocketFireTimer = 0.0f;
	}
}

unsigned int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(unsigned int score)
{
	if (mScoreTimer > mScoreRate)
	{
		mScore += score;
		mScoreTimer = 0.0f;
	}
}

void Player::RemoveScore(unsigned int score)
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

void Player::ToggleTexture()
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

void Player::Impact()
{
	impact = true;
}

void Player::Explode()
{
	exploded = true;
}

void Player::AddHealth()
{
	mLives++;
}

void Player::RemoveHealth()
{
	mLives--;
}

void Player::Hit(PhysicsEntity* other)
{
	std::cout << "Player1 got hit." << std::endl;
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

bool Player::IgnoreCollisions()
{
	return !Active();
}

void Player::Update()
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

void Player::Render()
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
		mPlayer->Render();
	}
	else if (ship)
	{
		mPlayerShip->Render();
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
