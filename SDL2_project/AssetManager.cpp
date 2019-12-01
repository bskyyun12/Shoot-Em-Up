#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto texture : mTextures)
	{
		if (texture.second != nullptr)
		{
			SDL_DestroyTexture(texture.second);
		}
	}

	mTextures.clear();

	for (auto text : mTexts)
	{
		if (text.second != nullptr)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	mTexts.clear();

	for (auto font : mFonts)
	{
		if (font.second != nullptr)
		{
			TTF_CloseFont(font.second);
		}
	}

	mFonts.clear();

	//Freeing all loaded music
	for (auto music : mMusics) {

		if (music.second != NULL) {

			Mix_FreeMusic(music.second);
		}
	}

	mMusics.clear();

	//Freeing all loaded sound effects
	for (auto sfx : mSFXs) {

		if (sfx.second != NULL) {

			Mix_FreeChunk(sfx.second);
		}
	}

	mSFXs.clear();
}

std::string AssetManager::GetPath()
{
	std::string fullPath = SDL_GetBasePath();

	for (int i = 0; i < 10; i++)
	{
		fullPath.pop_back();
	}

	return fullPath;
}

SDL_Texture* AssetManager::GetTexture(std::string fileName)
{
	std::string fullPath = GetPath();
	fullPath.append("Assets/" + fileName);

	//If the file has not been already loaded, load it and add it to the mTextures map
	if (mTextures[fullPath] == nullptr)
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);

	return mTextures[fullPath];
}

TTF_Font* AssetManager::GetFont(std::string fileName, int size)
{
	std::string fullPath = GetPath();
	fullPath.append("Assets/" + fileName);

	//The key takes into account the size of the font aswell since the same font can be opened with different sizes
	std::string key = fullPath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (mFonts[key] == nullptr)
		{
			printf("Font Loading Error: Font-%s Error-%s", fileName.c_str(), TTF_GetError());
			Logger::Log(TTF_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		}
	}

	return mFonts[key];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string fileName, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(fileName, size);

	//The key takes into account the font, text, size, and color to differentiate text textures
	std::string key = text + fileName + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (mTexts[key] == nullptr)
		mTexts[key] = Graphics::Instance()->CreateTextTexture(font, text, color);

	return mTexts[key];
}

Mix_Music* AssetManager::GetMusic(std::string fileName)
{
	std::string fullPath = GetPath();
	fullPath.append("Assets/" + fileName);

	if (mMusics[fullPath] == nullptr)
	{
		mMusics[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (mMusics[fullPath] == nullptr)
		{
			printf("Music Loading Error: File-%s Error-%s", fileName.c_str(), Mix_GetError());
			Logger::Log(Mix_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		}
	}

	return mMusics[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string fileName)
{
	std::string fullPath = GetPath();
	fullPath.append("Assets/" + fileName);

	if (mSFXs[fullPath] == nullptr)
	{
		mSFXs[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (mSFXs[fullPath] == nullptr)
		{
			printf("SFX Loading Error: File-%s Error-%s", fileName.c_str(), Mix_GetError());
			Logger::Log(Mix_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		}
	}
	return mSFXs[fullPath];
}
