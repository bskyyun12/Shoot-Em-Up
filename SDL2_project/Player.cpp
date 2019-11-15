#include "Player.h"

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

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}
	mFireTimer = 0.0f;
	mFireRate = 0.5f;
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
}

void Player::HandleMovement()
{
	//Hello
	// save player's position before player moves
	Vector2D prevPlayerPos = Pos(local);

	// Player Input
	if (mInputManager->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_DOWN))
	{
		Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime(), world);
	}

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
		HandleFiring();
	}

	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Player::Render()
{
	// bullet
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}

	mPlayer->Render();
}
