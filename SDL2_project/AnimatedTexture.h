#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H

#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture
{
public:
	
	enum WRAP_MODE { once = 0, loop = 1 };
	enum ANIM_DIR { horizontal = 0, vertical = 1 };

private:

	Timer* mTimer = nullptr;

	int mStartX;
	int mStartY;

	float mAnimationTimer;
	float mAnimationSpeed;
	float mTimePerFrame;

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimationDirection;

	bool mAnimationDone;

public:
	//---------------------------------------------------------------------------------
	//Loads a texture from from file (relative to the exe path)
	//Supports spritesheets
	//x - Starting pixel's X on the spritesheet
	//y - Starting pixel's Y on the spritesheet
	//w - The width of the clipped sprite
	//h - The height of the clipped sprite
	//frameCount - The number of frames in the animation
	//animationSpeed - How long it takes to run the animation in seconds t.e. 2.0f = 1 frame per 2 seconds
	//animationDirection - How the animation sprites are arranges in the spritesheet
	//---------------------------------------------------------------------------------
	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	~AnimatedTexture();

	bool IsAnimationDone();

	void WrapMode(WRAP_MODE mode);

	void Update();

};

#endif
