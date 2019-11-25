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
			case player1Projectile:
				// if playerProjectile is active
				if (col.first->Active())
				{
					// if playerProjectile hits enemy
					if (col2.second == enemy && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						col2.first->Active(false);
						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
					}
				}
				break;
			case player2Projectile:
				// if playerProjectile is active
				if (col.first->Active())
				{
					// if playerProjectile hits enemy
					if (col2.second == enemy && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						col2.first->Active(false);
						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
					}
				}
				break;
			case enemyProjectile:
				// if enemyProjectile is active
				if (col.first->Active())
				{
					// if enemyProjectile hits player1
					if (col2.second == player1 && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						col2.first->Active(false);
						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
					}
					// if enemyProjectile hits player2
					if (col2.second == player2 && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
					{
						col.first->Active(false);
						col2.first->Active(false);
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

std::string Collider::tagEnumToStr(int index)
{
	// debug purpose
	//	0 : player1,
	//	player2,
	//	enemy,
	//	player1Projectile,
	//	player2Projectile,
	//	enemyProjectile
	std::string s("unknown");
	switch (index)
	{
	case 0: { s = "Player1"; } break;
	case 1: { s = "Player2"; } break;
	case 2: { s = "Enemy"; } break;
	case 3: { s = "Player1Projectile"; } break;
	case 4: { s = "Player2Projectile"; } break;
	case 5: { s = "EnemyProjectile"; } break;
	}
	return s;
}
