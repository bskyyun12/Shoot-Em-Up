#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:
	
	SDL_Texture* mTex = nullptr;

	Graphics* mGraphics = nullptr;

	int mWidth;	 //Width of the texture
	int mHeight; //Height of the texture

	bool mCliped;

	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

public:
	//--------------------------------------------------------------
	//Loads a whole texture from a file (relative to the exe path)
	//Note: For spritesheets use the other contructor
	//--------------------------------------------------------------
	Texture(std::string filename);
	//-------------------------------------------------------------
	//Loads a texture from from file (relative to the exe path)
	//Supports spritesheets
	//x - Starting pixel's X on the spritesheet
	//y - Starting pixel's Y on the spritesheet
	//w - The width of the clipped sprite
	//h - The height of the clipped sprite
	//-------------------------------------------------------------
	Texture(std::string filename, int x, int y, int w, int h);
	//------------------------------------------------------------
	//Converts the given text into a texture to be rendered
	//Note: fontpath is relative to the exe path
	//size - The size of the text to be rendered
	//color - The color of the text to be rendered
	//------------------------------------------------------------
	Texture(std::string text, std::string fontpath, int size, SDL_Color color);
	~Texture();

	virtual void Render();

};

#endif