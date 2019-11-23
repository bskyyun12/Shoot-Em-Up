#pragma once
#include "Texture.h"
#include <map>
#include <iostream>


class Collider : public GameEntity
{
public:

	enum TAG
	{
		player1,
		player2,
		enemy,
		player1Projectile,
		player2Projectile,
		enemyProjectile
	};

private:

	static Collider* sInstance;

	std::map<Texture*, TAG> mColliders;

public:

	static Collider* Instance();
	static void Release();

	void AddCollider(Texture* tex, TAG tag);

	bool CheckCollision(Texture* tex, TAG tag);

	void Update();

private:

	Collider();
	~Collider();

	// debug purpose
	std::string tagEnumToStr(int index);

};