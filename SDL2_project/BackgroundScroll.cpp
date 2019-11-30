#include "BackgroundScroll.h"
#include <iostream>

bool BackgroundScroll::mScroll = true;

BackgroundScroll::BackgroundScroll()
{
	// Background Variables
	mBackgroundStartPos = Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mBackgroundEndPos = Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mScrollSpeed = 0.8f;
}

BackgroundScroll::~BackgroundScroll()
{
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		delete mBackgrounds[i];
		mBackgrounds[i] = nullptr;
	}
	mBackgrounds.clear();
}

void BackgroundScroll::AddBackgroundImage(std::string path, bool scroll)
{
	mTempTex1 = new Texture(path);
	mTempTex1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mTempTex1->ScaledDimensions().x, (float)Graphics::Instance()->SCREEN_HEIGHT / mTempTex1->ScaledDimensions().y));
	mTempTex1->Pos(mBackgroundStartPos);
	mBackgrounds.push_back(mTempTex1);

	if (scroll) // make same texture and add it next to first one
	{
		mTempTex2 = new Texture(path);
		mTempTex2->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mTempTex2->ScaledDimensions().x, (float)Graphics::Instance()->SCREEN_HEIGHT / mTempTex2->ScaledDimensions().y));
		mTempTex2->Pos(Vector2D(mTempTex1->Pos().x + Graphics::Instance()->SCREEN_WIDTH, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
		mTempTex2->Parent(mTempTex1);
		mBackgrounds.push_back(mTempTex2);
	}
}

void BackgroundScroll::SetBackground(std::string path, int backgroundAmount)
{
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		delete mBackgrounds[i];
		mBackgrounds[i] = nullptr;
	}
	mBackgrounds.clear();

	for (int i = 0; i < backgroundAmount; i++)
	{
		std::string tempPath = "";
		tempPath.append(path + std::to_string(i) + ".png");

		if (i == 0)
			AddBackgroundImage(tempPath, false);
		else
			AddBackgroundImage(tempPath);
	}
}

void BackgroundScroll::ResetBackgroundPos(Texture* background)
{
	if (background->Pos().x < mBackgroundEndPos.x)
		background->Pos(mBackgroundStartPos);
}

void BackgroundScroll::Update()
{
	if (mScroll)
	{
		//teseting
		for (int i = 1; i < mBackgrounds.size(); i += 2)
		{
			mBackgrounds[i]->Pos(mBackgrounds[i]->Pos() + VECTOR2D_LEFT * mScrollSpeed * (float)i);

			if (mBackgrounds[i]->Pos().x < mBackgroundEndPos.x)
				mBackgrounds[i]->Pos(mBackgroundStartPos);
		}
	}
}

void BackgroundScroll::Render()
{
	//teseting
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		mBackgrounds[i]->Render();
	}
}
