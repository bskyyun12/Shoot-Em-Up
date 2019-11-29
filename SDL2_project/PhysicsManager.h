#pragma once
#include "PhysicsEntity.h"
#include <bitset>

class PhysicsManager
{
public:
	enum class CollisionLayers {
		Player,
		PlayerProjectiles,
		Enemy,
		EnemyProjectiles,
		//-----------------------
		MaxLayers

	};

	enum class CollisionFlags {

		None				= 0x00,
		Player				= 0x01,
		PlayerProjectiles	= 0x02,
		Enemy				= 0x04,
		EnemyProjectiles	= 0x08,
	};

private:

	static PhysicsManager* sInstance;

	std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

public:

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:

	PhysicsManager();
	~PhysicsManager();

};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

