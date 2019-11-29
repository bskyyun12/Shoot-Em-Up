#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new GameManager();
	}
	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

// here initialize everything
GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
	{
		mQuit = true;
	}

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();

	mScreenManager = ScreenManager::Instance();

	mPhysicsManager = PhysicsManager::Instance();
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Player, PhysicsManager::CollisionFlags::Enemy | PhysicsManager::CollisionFlags::EnemyProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::PlayerProjectiles, PhysicsManager::CollisionFlags::Enemy);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Enemy, PhysicsManager::CollisionFlags::Player | PhysicsManager::CollisionFlags::PlayerProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::EnemyProjectiles, PhysicsManager::CollisionFlags::Player);

	mInputManager->CleanJoysticks();
	mInputManager->InitialiseJoysticks();
}

GameManager::~GameManager()
{
	PhysicsManager::Release();
	mPhysicsManager = nullptr;

	ScreenManager::Release();
	mScreenManager = nullptr;

	AudioManager::Release();
	mAudioManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;
}

void GameManager::EarlyUpdate() 
{
	//mInputManager->Update();
}

void GameManager::Update() 
{
	mScreenManager->Update();
}

void GameManager::LateUpdate() 
{
	mPhysicsManager->Update();
	mInputManager->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render() 
{
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	mScreenManager->Render();

	//Renders the current frame
	mGraphics->Render();
}


void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();
		mInputManager->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			switch (mEvents.type)
			{
			case SDL_QUIT:
				mQuit = true;
			default:
				break;
			}
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}
