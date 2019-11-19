#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player()
{
	// handel movement
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mMoveSpeed = 300.0f;	// per second
	mBoundsOffset = 32.0f;	// half of player image's size

	// init current score and lives
	mScore = 1234567;
	mLives = 3;

	// player texture
	mPlayer = new Texture("Jump (32x32).png");
	mPlayer->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mPlayer->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)
	
	// collider 
	mCollider = new BoxCollider(mPlayer, "player");
	AddCollider(mCollider);
	//AddCollider(new BoxCollider(Vector2D(mPlayer->ScaledDimensions().x * 5 / 8, mPlayer->ScaledDimensions().y * 5 / 16)), Vector2D(mPlayer->ScaledDimensions().x * 1 / 64, -mPlayer->ScaledDimensions().y * 6 / 64));
	//AddCollider(new BoxCollider(mPlayer->ScaledDimensions() * 0.5f), Vector2D(0.0f, mPlayer->ScaledDimensions().y * 10 / 64));

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}
	mFireTimer = 0.0f;
	mFireRate = 0.5f;

	// rocket
	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		mRockets[i] = new Rocket();
	}
	mRocketFireTimer = 0.0f;
	mRocketFireRate = 2.5f;
}

Player::~Player()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

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
	delete mCollider;
	mCollider = nullptr;
	
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

	if (mInputManager->KeyDown(SDL_SCANCODE_RCTRL)) // Shoot
	{
		HandleFiring();
	}

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased())
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(0, 1) > 0 || mInputManager->xValue(0, 1) < 0 ||
			mInputManager->yValue(0, 1) > 0 || mInputManager->yValue(0, 1) < 0)
		{
			cout << "LeftStickMove" << endl;
			Translate(Vector2D(mInputManager->xValue(0, 1), mInputManager->yValue(0, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(0, 2) > 0 || mInputManager->xValue(0, 2) < 0 ||
			mInputManager->yValue(0, 2) > 0 || mInputManager->yValue(0, 2) < 0)
		{
			cout << "RightStickMove" << endl;
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
			HandleFiring(); // Shoot
		}

		if (InputManager::Instance()->GetButtonState(0, 3)) // Yellow (Y) button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 4)) // LB button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 5)) // RB button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 6)) // Back/Select button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 7)) // Start button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 8)) // Left Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 9)) // Right Stick button
		{

		}

		if (InputManager::Instance()->GetButtonState(0, 10)) // XBOX button
		{

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

void Player::HandleFiring()
{
	mFireTimer += mTimer->DeltaTime();
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

	mRocketFireTimer += mTimer->DeltaTime();
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

void Player::Update()
{
	// player won't do anything during stage preparation
	if (Active())
	{
		HandleMovement();
		// Shoot with RCTRL or controller X button
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

	mPlayer->Render();

	// only for debug & visualizing. check collider position
	mCollider->Render();
}
