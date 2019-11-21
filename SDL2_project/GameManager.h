#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "AudioManager.h"
#include "Timer.h"
// STEP 1 : Include the new file you made
#include "ScreenManager.h"
#include "Collider.h"

class GameManager
{
private:

	static GameManager* sInstance;

	const int FRAME_RATE = 60;

	bool mQuit;

	Graphics* mGraphics = nullptr;
	AssetManager* mAssetManager = nullptr;
	InputManager* mInputManager = nullptr;
	AudioManager* mAudioManager = nullptr;

	Timer* mTimer = nullptr;

	SDL_Event mEvents = {0};

	// STEP 2 : Create new instance
	ScreenManager* mScreenManager = nullptr;
	Collider* mCollider = nullptr;

	// STEP 2 : Create new instance

public:

	static GameManager* Instance();
	static void Release();

	void Run();

private:

	GameManager();
	~GameManager();
	
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();

};

#endif // !_GAMEMANAGER_H
