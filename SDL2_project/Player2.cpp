#include "Player2.h"
#include <iostream>

using std::cout;
using std::endl;

Player2::Player2()
{
	// handle movement
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mMoveSpeed = 300.0f;	// per second
	mBoundsOffset = 32.0f;	// half of player image's size

	// init current score and lives
	mScore = 2222222;
	mLives = 3;

	// player texture
	mPlayer2 = new Texture("JumpBlue (32x32).png");
	mPlayer2->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mPlayer2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip2 = new AnimatedTexture("ship_80x48.png", 0, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip2->Rotate(90);
	mPlayerShip2->Scale(VECTOR2D_ONE * 4);	// scale up to 64x64
	mPlayerShip2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// collider 
	mCollider = Collider::Instance();
	mCollider->AddCollider(mPlayer2, Collider::TAG::player2);
	mCollider->AddCollider(mPlayerShip2, Collider::TAG::player2);

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
}

Player2::~Player2()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mPlayer2;
	mPlayer2 = nullptr;

	delete mPlayerShip2;
	mPlayerShip2 = nullptr;

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

	// collider
	mCollider = nullptr;

}

void Player2::HandleMovement()
{
	// save player's position before player moves
	Vector2D prevPlayerPos = Pos(local);

	// Player Input
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

	if (mInputManager->KeyDown(SDL_SCANCODE_F)) // Shoot
	{
		HandleFiring();
	}

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased() && mInputManager->GetNumberOfJoysticks() >= 2)
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(1, 1) > 0 || mInputManager->xValue(1, 1) < 0 ||
			mInputManager->yValue(1, 1) > 0 || mInputManager->yValue(1, 1) < 0)
		{
			cout << "LeftStickMove" << endl;
			Translate(Vector2D(mInputManager->xValue(1, 1), mInputManager->yValue(1, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(1, 2) > 0 || mInputManager->xValue(1, 2) < 0 ||
			mInputManager->yValue(1, 2) > 0 || mInputManager->yValue(1, 2) < 0)
		{
			cout << "RightStickMove" << endl;
			Translate(Vector2D(mInputManager->xValue(1, 2), mInputManager->yValue(1, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		if (InputManager::Instance()->GetButtonState(1, 0)) // Green (A) button
		{

		}

		if (InputManager::Instance()->GetButtonState(1, 1)) // Red (B) button
		{

		}

		if (InputManager::Instance()->GetButtonState(1, 2)) // Blue (X) button
		{
			HandleFiring(); // Shoot
		}

		if (InputManager::Instance()->GetButtonState(1, 3)) // Yellow (Y) button
		{
			
		}

		if (InputManager::Instance()->GetButtonState(1, 4)) // LB button
		{
			mPlayer2->Rotate(90);
		}

		if (InputManager::Instance()->GetButtonState(1, 5)) // RB button
		{
			HandleFiring(); // Shoot
		}

		if (InputManager::Instance()->GetButtonState(1, 6)) // Back/Select button
		{
			AddHealth();
			cout << "Player 2 Lives : " << mLives << endl;
		}

		if (InputManager::Instance()->GetButtonState(1, 7)) // Start button
		{
			RemoveHealth();
			cout << "Player 2 Lives : " << mLives << endl;
		}

		if (InputManager::Instance()->GetButtonState(1, 8)) // Left Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(1, 9)) // Right Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(1, 10)) // XBOX button
		{
			AddScore(1);
			cout << "Player 2 Score : " << mScore << endl;
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

void Player2::HandleFiring()
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

int Player2::Score()
{
	return mScore;
}

int Player2::Lives()
{
	return mLives;
}

void Player2::AddScore(int score)
{
	mScore += score;
}

void Player2::ToggleTexture()
{
	ship = !ship;
}

void Player2::AddHealth()
{
	mLives++;
}

void Player2::RemoveHealth()
{
	mLives--;
}

void Player2::Update()
{
	mFireTimer += mTimer->DeltaTime();
	mRocketFireTimer += mTimer->DeltaTime();

	// player won't do anything during stage preparation
	if (Active())
	{
		HandleMovement();
		//mCollider->Update(mPlayer2, Collider::TAG::player);
		// Shoot with F or controller X button or RB button
		//HandleFiring();
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

	if (!ship)
	{
		mPlayer2->Render();
	}
	else if (ship)
	{
		mPlayerShip2->Render();
	}
}
