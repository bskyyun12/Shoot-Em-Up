#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player()
{
	// handle movement
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mMoveSpeed = 300.0f;	// per second
	mBoundsOffset = 32.0f;	// half of player image's size

	// init current score and lives
	mScore = 1111111;
	mLives = 3;

	// player texture
	mPlayer = new Texture("JumpOrange (32x32).png");
	mPlayer->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mPlayer->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip = new AnimatedTexture("ship_80x48.png", 32, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip->Rotate(90);
	mPlayerShip->Scale(VECTOR2D_ONE * 4);	// scale up to 64x64
	mPlayerShip->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

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
<<<<<<< HEAD
	//mCollider->AddCollider(mPlayerShip, Collider::TAG::player);
=======
	mCollider->AddCollider(mPlayer, Collider::TAG::player1);
	mCollider->AddCollider(mPlayerShip, Collider::TAG::player1);
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
}

Player::~Player()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mPlayerShip;
	mPlayerShip = nullptr;

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

	if (mInputManager->KeyDown(SDL_SCANCODE_RCTRL)) // Fire Bullet
	{
		FireBullet();
	}

	if (mInputManager->KeyDown(SDL_SCANCODE_RSHIFT)) // Fire Rocket
	{
		FireRocket();
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
			Translate(Vector2D(mInputManager->xValue(0, 1), mInputManager->yValue(0, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(0, 2) > 0 || mInputManager->xValue(0, 2) < 0 ||
			mInputManager->yValue(0, 2) > 0 || mInputManager->yValue(0, 2) < 0)
		{
			//cout << "RightStickMove" << endl;
			Translate(Vector2D(mInputManager->xValue(0, 2), mInputManager->yValue(0, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		if (InputManager::Instance()->GetButtonState(0, 0)) // Green (A) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 1)) // Red (B) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 2)) // Blue (X) button
		{
			FireBullet(); // Fire bullet
		}

		if (InputManager::Instance()->GetButtonState(0, 3)) // Yellow (Y) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 4)) // LB button
		{
			mPlayer->Rotate(90);
		}

		if (InputManager::Instance()->GetButtonState(0, 5)) // RB button
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
		Pos().x > 950.0f ||
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

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int score)
{
	mScore += score;
}

void Player::ToggleTexture()
{
	ship = !ship;
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

<<<<<<< HEAD
		//if (mCollider->CollisionCheck(mPlayerShip, Collider::TAG::player))
		//{
		//	std::cout << "player needs to lose life!!" << std::endl;
		//}
		// Use This
		//RemoveHealth();
=======
#pragma region Collision detection

		if (!mPlayerShip->Active())
		{
			std::cout << "mPlayerShip gets damage." << std::endl;

			// here do things like losing life

			mPlayerShip->Active(true);
		}
		else if (!mPlayer->Active())
		{
			std::cout << "mPlayer gets damage." << std::endl;

			// here do things like losing life

			mPlayer->Active(true);
		}

#pragma endregion Collision detection

		// Shoot with RCTRL or controller X button or RB button
		//HandleFiring();
>>>>>>> 481c551444346b1af0d70987500dda6a0221fb93
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
}
