#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "BoxCollider.h"

class Bullet : public PhysicsEntity
{
private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	float mSpeed;

	AnimatedTexture* mBullet = nullptr;

	//collider
	Collider::TAG mTag;

public:

	Bullet(Collider::TAG tag);
	~Bullet();

	void Fire(Vector2D pos);
	void Reload();

	//collider
	void Hit(PhysicsEntity* other) override;

	void Update();
	void Render();

private:

	//collider
	bool IgnoreCollisions() override;
};

