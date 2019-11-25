#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "Collider.h"

class Bullet : public GameEntity
{
private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	float mSpeed;

	AnimatedTexture* mBullet = nullptr;

	//collider
	Collider* mCollider = nullptr;
	Collider::TAG mTag;

public:

	Bullet(Collider::TAG tag);
	~Bullet();

	void Fire(Vector2D pos);
	void Reload();

	void Update();
	void Render();
};

