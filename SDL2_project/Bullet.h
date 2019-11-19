#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"

class Bullet : public PhysicsEntity
{
private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	float mSpeed;

	AnimatedTexture* mBullet = nullptr;

	//collider
	Collider* mCollider = nullptr;

public:

	Bullet();
	~Bullet();

	void Fire(Vector2D pos);
	void Reload();

	void Update();
	void Render();
};

