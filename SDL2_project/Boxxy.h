#pragma once

#include "Enemy.h"

class Boxxy : public Enemy {
private:

	Vector2D FormationPosition();

	void Enemy::HandleDiveState();
	void Enemy::HandleDeadState();

public:

	Boxxy(int index, int path, bool challengeStage);
	~Boxxy();


};