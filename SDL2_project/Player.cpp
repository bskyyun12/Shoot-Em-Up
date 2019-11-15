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
}

Player::~Player()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void Player::HandleMovement()
{
	// save player's position before player moves
	Vector2D prevPlayerPos = Pos(local);

	// Player Input
	if (mInputManager->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_DOWN))
	{
		Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime());
	}

	// Set Player Move Bounds
	if (
		Pos(local).x < mBoundsOffset ||
		Pos(local).x > Graphics::Instance()->SCREEN_WIDTH - mBoundsOffset ||
		Pos(local).y < mBoundsOffset + 90.0f ||
		Pos(local).y > Graphics::Instance()->SCREEN_HEIGHT - mBoundsOffset
		)
	{
		Pos(prevPlayerPos);	// set position back to previous position
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
	// player won't move during stage preparation
	if (Active())
	{
		HandleMovement();
	}
}

void Player::Render()
{
	mPlayer->Render();
}
