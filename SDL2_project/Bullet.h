#pragma once
#include "AnimatedTexture.h"
#include "Timer.h"
#include "AudioManager.h"

class Bullet : public GameEntity
{
private:

	Timer* mTimer = nullptr;
	AudioManager* mAudioManager = nullptr;

	float mSpeed;

	AnimatedTexture* mBullet = nullptr;

public:

	Bullet();
	~Bullet();

	void Fire(Vector2D pos);
	void Reload();

	void Update();
	void Render();
};
