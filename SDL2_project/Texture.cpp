#include "Texture.h"

Texture::Texture(std::string fileName)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(fileName);

	//Gets the Width and Height of the texture
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mCliped = false;
	mClipRect = {};

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string fileName, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(fileName);

	mCliped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mCliped = false;
	mClipRect = {};

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	// We don't need to destroy textures here since AssetManager destroys all the textures instead
	mTex = nullptr;

	mGraphics = nullptr;
}

Vector2D Texture::ScaledDimensions()
{
	Vector2D scaledDimensions = Scale();
	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;

	return scaledDimensions;
}

void Texture::Render() {

	Vector2D pos = Pos(world);
	Vector2D scale = Scale(world);

	//Centers the texture on the texture's world position so that its position is not the top left corner
	mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);

	//Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, (mCliped) ? &mClipRect : NULL, &mRenderRect, Rotation(world));
}
