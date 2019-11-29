#include "Collider.h"

//Collider* Collider::sInstance = nullptr;
//
//Collider* Collider::Instance()
//{
//	if (sInstance == nullptr)
//	{
//		sInstance = new Collider();
//	}
//	return sInstance;
//}
//
//void Collider::Release()
//{
//	delete sInstance;
//	sInstance = nullptr;
//}
//
//Collider::Collider()
//{
//}

Collider::Collider(TAG tag) : mTag(tag)
{
	///
	mDebugTexture = nullptr;
	///
}

Collider::~Collider()
{
	///
	if (mDebugTexture)
	{
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
	///
}

void Collider::SetDebugTexture(Texture* texture)
{
	///
	delete mDebugTexture;
	mDebugTexture = texture;
	mDebugTexture->Parent(this);
	///
}

Collider::TAG Collider::GetTag()
{
	return mTag;
}

void Collider::Render()
{
	///
	if (DEBUG_COLLIDERS)
	{
		mDebugTexture->Render();
	}
	///
}
//
//void Collider::AddCollider(Texture* tex, TAG tag)
//{
//	if (mColliders.find(tex) == mColliders.end())
//	{
//		mColliders.insert(std::make_pair(tex, tag));
//		std::cout << "Added " << tagEnumToStr(tag) << "! mColliders size() : " << mColliders.size() << std::endl;
//	}
//	else
//	{
//		std::cout << tagEnumToStr(tag) << " exists already! mColliders size() : " << mColliders.size() << std::endl;
//	}
//}
//
//void Collider::RemoveCollider(Texture* tex)
//{
//	it = mColliders.find(tex);
//	std::cout << "Removed " << tagEnumToStr(it->second);
//	mColliders.erase(it);
//
//	std::cout << "! mColliders size() : " << mColliders.size() << std::endl;
//}
//
//void Collider::Update()
//{
//	for (auto col : mColliders)
//	{
//		for (auto col2 : mColliders)
//		{
//			switch (col.second)
//			{
//			case player1Projectile:
//				// if playerProjectile is active
//				if (col.first->Active())
//				{
//					// if playerProjectile hits enemy
//					if (col2.second == enemy && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
//					{
//						col.first->Active(false);
//						col2.first->Active(false);
//						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
//					}
//				}
//				break;
//			case player2Projectile:
//				// if playerProjectile is active
//				if (col.first->Active())
//				{
//					// if playerProjectile hits enemy
//					if (col2.second == enemy && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
//					{
//						col.first->Active(false);
//						col2.first->Active(false);
//						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
//					}
//				}
//				break;
//			case enemyProjectile:
//				// if enemyProjectile is active
//				if (col.first->Active())
//				{
//					// if enemyProjectile hits player1
//					if (col2.second == player1 && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
//					{
//						col.first->Active(false);
//						col2.first->Active(false);
//						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
//					}
//					// if enemyProjectile hits player2
//					if (col2.second == player2 && SDL_HasIntersection(&col.first->GetRect(), &col2.first->GetRect()))
//					{
//						col.first->Active(false);
//						col2.first->Active(false);
//						std::cout << tagEnumToStr(col.second) << " hits : " << tagEnumToStr(col2.second) << std::endl;
//					}
//				}
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}
//
//std::string Collider::tagEnumToStr(int index)
//{
//	// debug purpose
//	//	0 : player1,
//	//	1 : player2,
//	//	2 : enemy,
//	//	3 : player1Projectile,
//	//	4 : player2Projectile,
//	//	5 : enemyProjectile
//	std::string s("unknown");
//	switch (index)
//	{
//	case 0: { s = "Player1"; } break;
//	case 1: { s = "Player2"; } break;
//	case 2: { s = "Enemy"; } break;
//	case 3: { s = "Player1Projectile"; } break;
//	case 4: { s = "Player2Projectile"; } break;
//	case 5: { s = "EnemyProjectile"; } break;
//	}
//	return s;
//}
