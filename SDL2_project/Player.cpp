#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player()
{
	// handle movement
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
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

	// Player Input
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

	if (mInputManager->KeyDown(SDL_SCANCODE_RCTRL) && !shield) // Fire Bullet
	{
		FireBullet();
	}

	if (mInputManager->KeyDown(SDL_SCANCODE_RETURN) && !shield) // Fire Rocket
	{
		FireRocket();
		AddScore(1);
	}

	if (mInputManager->KeyDown(SDL_SCANCODE_BACKSPACE)) // Raise Shield 
	{
		mShield->Update();
		shield = true;
	}

	if (mInputManager->KeyReleased(SDL_SCANCODE_BACKSPACE)) // Lower Shield
	{
		shield = false;
	}

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased())
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(0, 1) > 0 || mInputManager->xValue(0, 1) < 0 ||
			mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 1) < 0)
		{
			//cout << "LeftStickMove" << endl;
			Translate(Vector2D((float)mInputManager->xValue(0, 1), (float)mInputManager->yValue(0, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(0, 2) > 0 || mInputManager->xValue(0, 2) < 0 ||
			mInputManager->yValue(0, 2) > 0 || mInputManager->yValue(0, 2) < 0)
		{
			//cout << "RightStickMove" << endl;
			Translate(Vector2D((float)mInputManager->xValue(0, 2), (float)mInputManager->yValue(0, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		if (InputManager::Instance()->GetButtonState(0, 0)) // Green (A) button
		{
			mPlayer->Rotate(90);
		}

		if (InputManager::Instance()->GetButtonState(0, 1)) // Red (B) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 2) && !shield) // Blue (X) button
		{
			FireBullet(); // Fire bullet
		}

		if (InputManager::Instance()->GetButtonState(0, 3)) // Yellow (Y) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 4)) // LB button
		{
			mShield->Update();
			shield = true;		// Raise Shield
		}

		// LB button
		if (!(InputManager::Instance()->GetButtonState(0, 4)) && shield && !(mInputManager->KeyDown(SDL_SCANCODE_BACKSPACE)))
		{
			shield = false;		// Lower Shield
		}

		if (InputManager::Instance()->GetButtonState(0, 5) && !shield) // RB button
		{
			FireRocket(); // Fire Rocket
		}

		if (InputManager::Instance()->GetButtonState(0, 6)) // Back/Select button
		{
			AddHealth();
			cout << "Player 1 Lives : " << mLives << endl;
		}

		if (InputManager::Instance()->GetButtonState(0, 7)) // Start button
		{
			RemoveHealth();
			cout << "Player 1 Lives : " << mLives << endl;
		}

		if (InputManager::Instance()->GetButtonState(0, 8)) // Left Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 9)) // Right Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 10)) // XBOX button
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

		//if (mCollider->CollisionCheck(mPlayerShip, Collider::TAG::player))
		//{
		//	std::cout << "player needs to lose life!!" << std::endl;
		//}

#pragma region Collision detection

		if (!mPlayerShip->Active())
		{
			std::cout << "mPlayerShip gets damage." << std::endl;

			// here do things like losing life
			if (!shield)
			{
				RemoveHealth();
			}
			Impact();
			mPlayerShip->Active(true);
		}
		else if (!mPlayer->Active())
		{
			std::cout << "mPlayer gets damage." << std::endl;

			// here do things like losing life
			if (!shield)
			{
				RemoveHealth();
			}
			Impact();
			mPlayer->Active(true);
		}

#pragma endregion Collision detection

		if (impact)
		{
			mImpact->Update();
		}

		if (mImpact->IsAnimationDone())
		{
			impact = false;
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

	if (!ship)
	{
		mPlayer->Render();
	}
	else if (ship)
	{
		mPlayerShip->Render();
	}

	if (impact)
	{
		mImpact->Render();
	}

	if (shield)
	{
		mShield->Render();
	}
}
