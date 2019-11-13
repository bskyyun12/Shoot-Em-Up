#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Logger.h"

class Graphics
{
public:
	
	static const int SCREEN_WIDTH = 1366;
	static const int SCREEN_HEIGHT = 768;
	const char* WINDOW_TITLE = "Team 3";
	const char* FONT = "Emulogic.ttf";

private:

	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

public:

	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	//----------------------------------------------------------------------------------
	//Loads a texture from file using the given path
	//Note: Should only be used by the AssetManager to cache the textures for reuse
	//----------------------------------------------------------------------------------
	SDL_Texture* LoadTexture(std::string path);
	//----------------------------------------------------------------------------------
	//renders a texture from using the given font and text
	//Note: Should only be used by the AssetManager to cache the textures for reuse
	//----------------------------------------------------------------------------------
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();

	//------------------------------------------------
	//Draws the given texture to the back buffer
	//------------------------------------------------
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Render();

private:

	Graphics();
	~Graphics();

	bool Init();

};

#endif // !_GRAPHICS_H
