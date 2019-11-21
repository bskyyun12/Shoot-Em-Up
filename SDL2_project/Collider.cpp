#include "Collider.h"

Collider* Collider::sInstance = nullptr;

Collider* Collider::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Collider();
	}
	return sInstance;
}

void Collider::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::AddCollider(Texture* tex, TAG tag)
{
	mColliders.insert(std::make_pair(tex, tag));
}

void Collider::Update()
{
	for (auto col : mColliders)
	{
		for (auto col2 : mColliders)
		{
			switch (col.second)
			{
			case playerProjectile:
				// if playerProjectile is active
				if (col.first->Active())
				{
					// if playerProjectile hits enemy
					if (col2.second == enemy && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
					}
				}
				break;
			case enemyProjectile:
				// if enemyProjectile is active
				if (col.first->Active())
				{
					// if enemyProjectile hits player
					if (col2.second == player && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void Collider::Render()
{

}

std::string Collider::tagEnumToStr(int index)
{
	// debug purpose
	std::string s("unknown");
	switch (index)
	{
	case 0: { s = "Player"; } break;
	case 1: { s = "Enemy"; } break;
	case 2: { s = "PlayerProjectile"; } break;
	case 3: { s = "EnemyProjectile"; } break;
	}
	return s;
}
