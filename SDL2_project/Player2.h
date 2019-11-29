#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Rocket.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

class Player2 : public PhysicsEntity
{
private:

	// handel movement
	Timer* mTimer = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;
	float mMoveSpeed;
	float mBoundsOffset;

	// init current score and lives
	unsigned int mScore;
	int mLives;

	// player texture
	Texture* mPlayer2 = nullptr;
	AnimatedTexture* mPlayerShip2 = nullptr;
	bool ship;

	// shield texture
	AnimatedTexture* mShield = nullptr;
	bool shield;

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
	bool mWasHit;

	// Impact
	AnimatedTexture* mImpact = nullptr;
	bool impact;

	// Explosion
	AnimatedTexture* mExplosion = nullptr;
	bool exploded;
	bool playOnce;

private:

	// Player movemonet logic
	void HandleMovement();

	// fire logic
	void FireBullet();
	void FireRocket();

public:

	Player2();
	~Player2();

	void ToggleTexture();
	void Impact();
	void Explode();

	// Player health
	void AddHealth();
	void RemoveHealth();

	// Collider
	void Hit(PhysicsEntity* other) override;
	bool IgnoreCollisions();

	// Get Player's current score
	unsigned int Score();
	// Get Player's current Lives
	int Lives();

	// Add score to Player's current score
	void AddScore(unsigned int score);

	void Update();
	void Render();

};

