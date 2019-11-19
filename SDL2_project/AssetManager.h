#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include <map>
#include <SDL_mixer.h>
#include "Graphics.h"

class AssetManager
{
private:

	static AssetManager* sInstance;

	std::map<std::string, SDL_Texture*> mTextures;
	std::map<std::string, SDL_Texture*> mTexts;
	std::map<std::string, TTF_Font*> mFonts;
	std::map<std::string, Mix_Music*> mMusics;
	std::map<std::string, Mix_Chunk*> mSFXs;

public:
	static AssetManager* Instance();
	static void Release();

	std::string GetPath();

	//----------------------------------------------------------------------------------------------
	//Should be used when any texture needs to be loaded from file
	//If the texture was not previously loaded, it is loaded from file then cached are returned
	//otherwise, the already cached texture is returned
	//----------------------------------------------------------------------------------------------
	SDL_Texture* GetTexture(std::string fileName);

	//-------------------------------------------------------------------------------------------------------------------
	//If the given text with the same font and size and color was renderer previously, the cached texture is returned
	//If it has not been rendered before, the text is rendered and cached, then returned to be reused again later
	//-------------------------------------------------------------------------------------------------------------------
	SDL_Texture* GetText(std::string text, std::string fileName, int size, SDL_Color color);

	//------------------------------------------------------------------------------------------
	//If the music file was opened before, the cached Mix_Music* is returned
	//otherwise, the file is loaded and converted into a Mix_Music* and cached then returned
	//------------------------------------------------------------------------------------------
	Mix_Music* GetMusic(std::string fileName);

	//------------------------------------------------------------------------------------------
	//If the SFX file was opened before, the cached Mix_Chunk* is returned
	//otherwise, the file is loaded and converted into a Mix_Chunk* and cached then returned
	//------------------------------------------------------------------------------------------
	Mix_Chunk* GetSFX(std::string fileName);

private:

	AssetManager();
	~AssetManager();

	//-----------------------------------------------------------------------------------
	//If the same font and size was loaded before, the cached TTF_Font* is returned
	//otherwise, the font is loaded and cached, then returned
	//-----------------------------------------------------------------------------------
	TTF_Font* GetFont(std::string fileName, int size);
};
#endif