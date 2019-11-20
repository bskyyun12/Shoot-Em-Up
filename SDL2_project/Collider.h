#pragma once
#include "Texture.h"
#include <map>
#include <iostream>


class Collider : public GameEntity
{
public:

	enum TAG
	{
		player,
		enemy,
		playerProjectile,
		enemyProjectile
	};

private:

	static Collider* sInstance;

	Texture* mDebugBox = nullptr;

	std::map<TAG, SDL_Rect> mColliders;
	SDL_Rect mRect;
	TAG mTag;

public:

	static Collider* Instance();
	static void Release();

	void AddCollider(Texture* tex, TAG tag);

	void Update(Texture* tex, TAG tag);
	void Render();

private:

	Collider();
	~Collider();

	// debug purpose
	std::string tagEnumToStr(int index);
	void Print(SDL_Rect rect);

};