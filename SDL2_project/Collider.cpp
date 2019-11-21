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

	mRect = { 0, 0, 0, 0 };

	mTag = player;
}

Collider::~Collider()
{
	delete mDebugBox;
	mDebugBox = nullptr;
}

void Collider::AddCollider(Texture* tex, TAG tag)
{
	mDebugBox->Scale(tex->ScaledDimensions() / 100.0f);
	mDebugBox->Parent(tex);
}

void Collider::Update(Texture* tex, TAG tag)
{
	mRect.x = (int)tex->Pos().x;
	mRect.y = (int)tex->Pos().y;
	mRect.w = (int)tex->ScaledDimensions().x;
	mRect.h = (int)tex->ScaledDimensions().y;

	mTag = tag;

	mColliders[mTag] = mRect;

	for (auto col : mColliders)
	{
		switch (tag)
		{
		case player:

#pragma region Test purpose. need to delete later
			switch (col.first)
			{
			case playerProjectile:
				if (SDL_HasIntersection(&mColliders[tag], &col.second))
				{
					// todo : do something when enemy hits player
					std::cout << tagEnumToStr(tag) << " hits : " << tagEnumToStr(col.first) << '\n';
					break;
				}
				break;
			default:
				break;
			}
#pragma endregion Test purpose. need to delete later

			break;
		case enemy:
			switch (col.first)
			{
			case player:
				if (SDL_HasIntersection(&mColliders[tag], &col.second))
				{
					// todo : do something when enemy hits player
					std::cout << tagEnumToStr(tag) << " hits : " << tagEnumToStr(col.first) << '\n';
					break;
				}
				break;
			default:
				break;
			}
			break;
		case playerProjectile:
			switch (col.first)
			{
			case enemy:
				if (SDL_HasIntersection(&mColliders[tag], &col.second))
				{
					// todo : do something when playerProjectile hits enemy
					std::cout << tagEnumToStr(tag) << " hits : " << tagEnumToStr(col.first) << '\n';
					break;
				}
				break;
			default:
				break;
			}
			break;
		case enemyProjectile:
			switch (col.first)
			{
			case player:
				if (SDL_HasIntersection(&mColliders[tag], &col.second))
				{
					// todo : do something when enemyProjectile hits player
					std::cout << tagEnumToStr(tag) << " hits : " << tagEnumToStr(col.first) << '\n';
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Collider::Render()
{
	mDebugBox->Render();
}

void Collider::Print(SDL_Rect rect)
{
	std::cout << "{" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << "}" << std::endl;
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
