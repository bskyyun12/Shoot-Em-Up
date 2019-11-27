#include "Player2.h"
#include <iostream>

using std::cout;
using std::endl;

Player2::Player2()
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
	mPlayer2 = new Texture("jumpBlue.png");
	mPlayer2->Scale(VECTOR2D_ONE * 2);	// scale up to 64x64
	mPlayer2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// PlayerShip AnimatedTexture
	mPlayerShip2 = new AnimatedTexture("shipBlue.png", 32, 0, 16, 24, 5, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mPlayerShip2->Rotate(90);
	mPlayerShip2->Scale(VECTOR2D_ONE * 4);	// scale up to 64x64
	mPlayerShip2->Parent(this);	// set mPlayer as a child of this script(in this way, it's easier to change the player's transform in other scripts)

	// Impact texture
	mImpact = new AnimatedTexture("impact.png", 0, 0, 50, 50, 8, 0.1f, AnimatedTexture::horizontal);
	mImpact->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mImpact->Parent(this);
	mImpact->Translate(VECTOR2D_RIGHT * 60);
	impact = false;

	// Shield texture
	mShield = new AnimatedTexture("shieldPurple.png", 0, 0, 45, 100, 4, 0.25f, AnimatedTexture::horizontal);
	mShield->Parent(this);
	mShield->Translate(VECTOR2D_RIGHT * 40);
	shield = false;

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
	mCollider = Collider::Instance();
	mCollider->AddCollider(mPlayer2, Collider::TAG::player2);
	mCollider->AddCollider(mPlayerShip2, Collider::TAG::player2);
}

Player2::~Player2()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	// collider
	mCollider = nullptr;

	// textures
	delete mPlayer2;
	mPlayer2 = nullptr;

	delete mPlayerShip2;
	mPlayerShip2 = nullptr;

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

	if (mInputManager->KeyDown(SDL_SCANCODE_F) && !shield) // Fire Bullet
	{
		FireBullet();
	}

	if (mInputManager->KeyDown(SDL_SCANCODE_SPACE) && !shield) // Fire Rocket
	{
		FireRocket();
		AddScore(1);
	}

	if (mInputManager->KeyDown(SDL_SCANCODE_Q)) // Raise Shield 
	{
		mShield->Update();
		shield = true;
	}

	if (mInputManager->KeyReleased(SDL_SCANCODE_Q)) // Lower Shield
	{
		shield = false;
	}

#pragma region Gamepad Input

	if (mInputManager->JoysticksInitialiased() && mInputManager->GetNumberOfJoysticks() >= 2)
	{

#pragma region Joysticks

		// left stick move
		if (mInputManager->xValue(1, 1) > 0 || mInputManager->xValue(1, 1) < 0 ||
			mInputManager->yValue(1, 1) > 0 || mInputManager->yValue(1, 1) < 0)
		{
			//cout << "LeftStickMove" << endl;
			Translate(Vector2D((float)mInputManager->xValue(1, 1), (float)mInputManager->yValue(1, 1)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

		// right stick move
		if (mInputManager->xValue(1, 2) > 0 || mInputManager->xValue(1, 2) < 0 ||
			mInputManager->yValue(1, 2) > 0 || mInputManager->yValue(1, 2) < 0)
		{
			//cout << "RightStickMove" << endl;
			Translate(Vector2D((float)mInputManager->xValue(1, 2), (float)mInputManager->yValue(1, 2)).Normalized() * mMoveSpeed * mTimer->DeltaTime(), world);
		}

#pragma endregion

#pragma region Buttons

		if (InputManager::Instance()->GetButtonState(1, 0)) // Green (A) button
		{
			mPlayer2->Rotate(90);
		}

		if (InputManager::Instance()->GetButtonState(1, 1)) // Red (B) button
		{

		}

		if (InputManager::Instance()->GetButtonState(1, 2)) // Blue (X) button
		{
			FireBullet(); // Fire Bullet
		}

		if (InputManager::Instance()->GetButtonState(1, 3)) // Yellow (Y) button
		{
			
		}

		if (InputManager::Instance()->GetButtonState(1, 4)) // LB button
		{
			mShield->Update();
			shield = true;		// Raise Shield
		}

		// LB button
		if (!(InputManager::Instance()->GetButtonState(1, 4)) && shield && !(mInputManager->KeyDown(SDL_SCANCODE_Q)))
		{
			shield = false;		// Lower Shield
		}

		if (InputManager::Instance()->GetButtonState(1, 5)) // RB button
		{
			FireRocket(); // Fire Rocket
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
	mScore += score;
}

void Player2::ToggleTexture()
{
	ship = !ship;

	if (ship)
	{
		mCollider->RemoveCollider(mPlayer2);
		mCollider->AddCollider(mPlayerShip2, Collider::TAG::player1);
	}
	else
	{
		mCollider->RemoveCollider(mPlayerShip2);
		mCollider->AddCollider(mPlayer2, Collider::TAG::player1);
	}
}

void Player2::Impact()
{
	impact = true;
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
		
		//if (mCollider->CollisionCheck(mPlayerShip, Collider::TAG::player))
		//{
		//	std::cout << "player needs to lose life!!" << std::endl;
		//}

#pragma region Collision detection

		if (!mPlayerShip2->Active())
		{
			std::cout << "mPlayerShip2 gets damage." << std::endl;

			// here do things like losing life
			if (!shield)
			{
				RemoveHealth();
			}
			Impact();
			mPlayerShip2->Active(true);
		}
		else if (!mPlayer2->Active())
		{
			std::cout << "mPlayer2 gets damage." << std::endl;

			// here do things like losing life
			if (!shield)
			{
				RemoveHealth();
			}
			Impact();
			mPlayer2->Active(true);
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

	if (impact)
	{
		mImpact->Render();
	}

	if (shield)
	{
		mShield->Render();
	}
}
