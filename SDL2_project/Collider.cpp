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
	mDebugBox = new Texture("BoxCollider.png");
}

Collider::~Collider()
{
	for (int i = 0; i < mDebugBoxes.size(); i++)
	{
		delete mDebugBoxes[i];
		mDebugBoxes[i] = nullptr;
	}
}

void Collider::AddCollider(Texture* tex, TAG tag)
{
	mColliders.insert(std::make_pair(tex, tag));

	mDebugBox->Scale(tex->ScaledDimensions() / 100.0f);
	mDebugBox->Pos(VECTOR2D_ZERO);
	mDebugBox->Parent(tex);
	mDebugBoxes.push_back(mDebugBox);
}

bool Collider::CollisionCheck(Texture* tex, TAG tag)
{
	for (auto col : mColliders)
	{
		switch (tag)
		{
		case player:
			if (col.second == enemy)
			{
				if (SDL_HasIntersection(&tex->GetRect(), &col.first->GetRect()))
				{
					std::cout << tagEnumToStr(tag) << " gets hit by " << tagEnumToStr(col.second) << std::endl;
					return true;
				}
			}
			else if (col.second == enemyProjectile)
			{
				if (SDL_HasIntersection(&tex->GetRect(), &col.first->GetRect()))
				{
					std::cout << tagEnumToStr(tag) << " gets hit by " << tagEnumToStr(col.second) << std::endl;
					return true;
				}
			}

#pragma region Testing.. Remove later
			else if (col.second == playerProjectile)
			{
				if (SDL_HasIntersection(&tex->GetRect(), &col.first->GetRect()))
				{
					std::cout << tagEnumToStr(tag) << " gets hit by " << tagEnumToStr(col.second) << std::endl;
					return true;
				}
			}
#pragma endregion Testing.. Remove later

			break;
		case enemy:
			if (col.second == playerProjectile)
			{
				if (SDL_HasIntersection(&tex->GetRect(), &col.first->GetRect()))
				{
					std::cout << tagEnumToStr(tag) << " gets hit by " << tagEnumToStr(col.second) << std::endl;
					return true;
				}
			}
			break;
		default:
			break;
		}
	}

	return false;
}

void Collider::Update()
{

}

void Collider::Render()
{
	for (int i = 0; i < mDebugBoxes.size(); i++)
	{
		mDebugBoxes[i]->Render();
	}
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
