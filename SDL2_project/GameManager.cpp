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

	// STEP 3 : Create new instance
	mScreenManager = ScreenManager::Instance();
	mCollider = Collider::Instance();

	// STEP 3 : Create new instance

	mInputManager->CleanJoysticks();
	mInputManager->InitialiseJoysticks();
}

GameManager::~GameManager()
{
	// STEP 4 : Delete instance
	ScreenManager::Release();
	mScreenManager = nullptr;

	Collider::Release();
	mCollider = nullptr;

	// STEP 4 : Delete instance

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
	// STEP 5 : Update the instance
	mScreenManager->Update();

	// STEP 5 : Update the instance
}

void GameManager::LateUpdate() 
{
	//Any collision detection should happen here
	mCollider->Update();
	mInputManager->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render() 
{
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	// STEP 6 : Render the instance
	mScreenManager->Render();
	mCollider->Render();

	// STEP 6 : Render the instance

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
