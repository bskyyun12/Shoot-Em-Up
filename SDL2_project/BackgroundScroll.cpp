#include "BackgroundScroll.h"

bool BackgroundScroll::mScroll = true;

BackgroundScroll::BackgroundScroll()
{
	// Timer
	mTimer = Timer::Instance();

	// Background Variables
	mBackgroundStartPos = Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mBackgroundEndPos = Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mScrollSpeed = 0.8f;

	AddBackground("Backgrounds/demon/demon_woods1.png", false);
	AddBackground("Backgrounds/demon/demon_woods2.png");
	AddBackground("Backgrounds/demon/demon_woods3.png");
	AddBackground("Backgrounds/demon/demon_woods4.png");
	//AddBackground("Backgrounds/5.png");

}

BackgroundScroll::~BackgroundScroll()
{
	//teseting
	mTempTex1 = nullptr;
	mTempTex2 = nullptr;
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		delete mBackgrounds[i];
		mBackgrounds[i] = nullptr;
	}
}

void BackgroundScroll::AddBackground(std::string path, bool scroll)
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
			mBackgrounds[i]->Pos(mBackgrounds[i]->Pos() + VECTOR2D_LEFT * mScrollSpeed * i);

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
