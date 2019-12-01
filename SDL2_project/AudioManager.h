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
	//Sets the BGM to play using the provided file, 
	//loops = -1 is infinite looping (default: -1)
	//loops = 0 is no looping, just once
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

	//---------------------------------------------------------------------------
	//Music volume, from 0 to MIX_MAX_VOLUME(128).
	//Values greater than MIX_MAX_VOLUME will use MIX_MAX_VOLUME.
	//- 1 does not set the volume, but does return the current volume setting.
	//---------------------------------------------------------------------------
	void MusicVolume(int volume);

	void SFXVolume(int channel, int volume);

	//--------------------------------------------------
	//Plays a sound effect from the file provided
	//plays if for the given loops (default: 0)
	//on the given channel (default: 0)
	//--------------------------------------------------
	void PlaySFX(std::string filename, int loops = 0, int channel = 0);
	void PauseSFX(int channel = -1);
	void ResumeSFX(int channel = -1);

private:
	
	AudioManager();
	~AudioManager();
};

#endif

