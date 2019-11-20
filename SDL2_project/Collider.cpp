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
		for (auto col2 : mColliders)
		{
			if (col.first != col2.first)
			{
				if (SDL_HasIntersection(&col.second, &col2.second))
				{
					std::cout << tagEnumToStr(col.first) << " hits : " << tagEnumToStr(col2.first) << '\n';
				}
			}
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
