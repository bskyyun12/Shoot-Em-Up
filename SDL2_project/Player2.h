#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Rocket.h"

class Player2 : public GameEntity
{
private:

	// handel movement
	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	float mMoveSpeed;
	float mBoundsOffset;

	// init current score and lives
	int mScore;
	int mLives;

	// player texture
	Texture* mPlayer2 = nullptr;
	AnimatedTexture* mPlayerShip2 = nullptr;

	// bullet
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS] = { nullptr };
	float mFireTimer;
	float mFireRate;

	//rocket
	static const int MAX_ROCKETS = 2;
	Rocket* mRockets[MAX_ROCKETS] = { nullptr };
	float mRocketFireTimer;
	float mRocketFireRate;

	// collider
	Collider* mCollider = nullptr;

	bool ship;

private:

	// Player movemonet logic
	void HandleMovement();

	// bullet fire logic
	void HandleFiring();

public:

	Player2();
	~Player2();

	void ToggleTexture();

	// Get Player's current score
	int Score();
	// Get Player's current Lives
	int Lives();

	// Add score to Player's current score
	void AddScore(int score);

	void Update();
	void Render();

};

