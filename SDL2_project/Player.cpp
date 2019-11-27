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

	// player texture
	mPlayer = new Texture("jumpOrange.png");
	mPlayer->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mPlayer->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip = new AnimatedTexture("shipRed.png", 32, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip->Rotate(90);
	mPlayerShip->Scale(VECTOR2D_ONE * 4);	// scale up to 64x64
	mPlayerShip->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)
	ship = false;

	// Impact texture
	mImpact = new AnimatedTexture("impact.png", 0, 0, 50, 50, 8, 0.1f, AnimatedTexture::horizontal);
	mImpact->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mImpact->Parent(this);
	mImpact->Translate(VECTOR2D_RIGHT * 60);
	impact = false;

	// Shield texture
	mShield = new AnimatedTexture("shieldBlue.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShield->Parent(this);
	mShield->Translate(VECTOR2D_RIGHT * 40);
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
	mCollider = Collider::Instance();
	mCollider->AddCollider(mPlayer, Collider::TAG::player1);
	mCollider->AddCollider(mPlayerShip, Collider::TAG::player1);
}

Player::~Player()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	// collider
	mCollider = nullptr;

	// textures
	delete mPlayer;
	mPlayer = nullptr;

	delete mPlayerShip;
	mPlayerShip = nullptr;

	delete mImpact;
	mImpact = nullptr;

	delete mShield;
	mShield = nullptr;

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
			AddScore(1);
		}

		// Raise Shield 
		if (mInputManager->KeyDown(SDL_SCANCODE_BACKSPACE))
		{
			mShield->Update();
			shield = true;
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
		if (InputManager::Instance()->GetButtonState(0, 4)) 
		{
			mShield->Update();
			shield = true;		// Raise Shield
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
			AddHealth();
			cout << "Player 1 Lives : " << mLives << endl;
		}

		// Start button
		if (InputManager::Instance()->GetButtonState(0, 7)) 
		{
			RemoveHealth();
			cout << "Player 1 Lives : " << mLives << endl;
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
			AddScore(1);
			cout << "Player 1 Score : " << mScore << endl;
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
	mScore += score;
}

void Player::ToggleTexture()
{
	ship = !ship;

	if (ship)
	{
		mCollider->RemoveCollider(mPlayer);
		mCollider->AddCollider(mPlayerShip, Collider::TAG::player1);
	}
	else
	{
		mCollider->RemoveCollider(mPlayerShip);
		mCollider->AddCollider(mPlayer, Collider::TAG::player1);
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

void Player::Update()
{
	mFireTimer += mTimer->DeltaTime();
	mRocketFireTimer += mTimer->DeltaTime();

	// player won't do anything during stage preparation
	if (Active())
	{
		HandleMovement();

#pragma region Collision detection

		if (!mPlayerShip->Active())
		{
			std::cout << "mPlayerShip gets damage." << std::endl;

			// here do things like losing life
			Impact();
			if (!shield)
			{
				RemoveHealth();
				if (mLives <= 0)
				{
					exploded = true;
				}
			}
			mPlayerShip->Active(true);
		}
		else if (!mPlayer->Active())
		{
			std::cout << "mPlayer gets damage." << std::endl;

			// here do things like losing life
			Impact();
			if (!shield)
			{
				RemoveHealth();
				if (mLives <= 0)
				{
					exploded = true;
				}
			}
			mPlayer->Active(true);
		}

#pragma endregion Collision detection

		if (impact && !exploded)
		{
			mImpact->Update();
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
			if (ship)
			{
				mCollider->RemoveCollider(mPlayerShip);
			}
			else
			{
				mCollider->RemoveCollider(mPlayer);
			}
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
		mShield->Render();
	}
}
