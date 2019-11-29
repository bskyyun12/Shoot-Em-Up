#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "AudioManager.h"
#include "Timer.h"
#include "ScreenManager.h"
#include "PhysicsManager.h"

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

	ScreenManager* mScreenManager = nullptr;
	PhysicsManager* mPhysicsManager = nullptr;

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
