#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H
#include "AssetManager.h"

class AudioManager
{
private:

	static AudioManager* sInstance;

	AssetManager* mAssetManager = nullptr;

public:

	static AudioManager* Instance();
	static void Release();

	//----------------------------------------------------------------------------------------------
	//Sets the BGM to play using the provided file, loops = -1 is infinite looping (default: -1)
	//-----------------------------------------------------------------------------------------------
	void PlayMusic(std::string filename, int loops = -1);
	//-------------------------------------------------------
	//Pauses the currently playing BGM if there is any
	//-------------------------------------------------------
	void PauseMusic();
	//-------------------------
	//Resumes paused BGM
	//-------------------------
	void ResumeMusic();

	//--------------------------------------------------
	//Plays a sound effect from the file provided
	//plays if for the given loops (default: 0)
	//on the given channel (default: 0)
	//--------------------------------------------------
	void PlaySFX(std::string filename, int loops = 0, int channel = 0);

private:
	
	AudioManager();
	~AudioManager();
};

#endif

