#include "BackgroundScroll.h"

bool BackgroundScroll::mScroll = true;

BackgroundScroll::BackgroundScroll()
{
	// Timer
	mTimer = Timer::Instance();

	// Background Variables
	mBackgroundImageWidth = 384.0f;
	mBackgroundImageHeight = 216.0f;	
	mBackgroundStartPos = Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mBackgroundEndPos = Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f);
	mScrollSpeed = 0.8f;

	// Background 1 - static
	mBackground_1 = new Texture("Backgrounds/plx-1.png");
	mBackground_1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));

	// Background 2
	mBackground_2 = new Texture("Backgrounds/plx-2.png");
	mBackground_2->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));

	mBackground_2_1 = new Texture("Backgrounds/plx-2.png");
	mBackground_2_1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));
	mBackground_2_1->Pos(Vector2D(mBackground_2->Pos().x + Graphics::Instance()->SCREEN_WIDTH, 0.0f));

	mBackground_2_1->Parent(mBackground_2);

	// Background 3
	mBackground_3 = new Texture("Backgrounds/plx-3.png");
	mBackground_3->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));

	mBackground_3_1 = new Texture("Backgrounds/plx-3.png");
	mBackground_3_1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));
	mBackground_3_1->Pos(Vector2D(mBackground_3->Pos().x + Graphics::Instance()->SCREEN_WIDTH, 0.0f));

	mBackground_3_1->Parent(mBackground_3);

	// Background 4
	mBackground_4 = new Texture("Backgrounds/plx-4.png");
	mBackground_4->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));

	mBackground_4_1 = new Texture("Backgrounds/plx-4.png");
	mBackground_4_1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));
	mBackground_4_1->Pos(Vector2D(mBackground_4->Pos().x + Graphics::Instance()->SCREEN_WIDTH, 0.0f));

	mBackground_4_1->Parent(mBackground_4);

	// Background 5
	mBackground_5 = new Texture("Backgrounds/plx-5.png");
	mBackground_5->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));

	mBackground_5_1 = new Texture("Backgrounds/plx-5.png");
	mBackground_5_1->Scale(Vector2D((float)Graphics::Instance()->SCREEN_WIDTH / mBackgroundImageWidth, (float)Graphics::Instance()->SCREEN_HEIGHT / mBackgroundImageHeight));
	mBackground_5_1->Pos(Vector2D(mBackground_5->Pos().x + Graphics::Instance()->SCREEN_WIDTH, 0.0f));

	mBackground_5_1->Parent(mBackground_5);

	// initialize positions
	mBackground_1->Pos(mBackgroundStartPos);
	mBackground_2->Pos(mBackgroundStartPos);
	mBackground_3->Pos(mBackgroundStartPos);
	mBackground_4->Pos(mBackgroundStartPos);
	mBackground_5->Pos(mBackgroundStartPos);
}

BackgroundScroll::~BackgroundScroll()
{
	//Freeing Background Entities
	delete mBackground_1;
	mBackground_1 = nullptr;
	delete mBackground_2_1;
	mBackground_2_1 = nullptr;
	delete mBackground_3;
	mBackground_3 = nullptr;
	delete mBackground_3_1;
	mBackground_3_1 = nullptr;
	delete mBackground_4;
	mBackground_4 = nullptr;
	delete mBackground_4_1;
	mBackground_4_1 = nullptr;
	delete mBackground_5;
	mBackground_5 = nullptr;
	delete mBackground_5_1;
	mBackground_5_1 = nullptr;
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
		mBackground_2->Pos(mBackground_2->Pos() + VECTOR2D_LEFT * mScrollSpeed);
		mBackground_3->Pos(mBackground_3->Pos() + VECTOR2D_LEFT * mScrollSpeed * 2);
		mBackground_4->Pos(mBackground_4->Pos() + VECTOR2D_LEFT * mScrollSpeed * 3);
		mBackground_5->Pos(mBackground_5->Pos() + VECTOR2D_LEFT * mScrollSpeed * 4);

		ResetBackgroundPos(mBackground_2);
		ResetBackgroundPos(mBackground_3);
		ResetBackgroundPos(mBackground_4);
		ResetBackgroundPos(mBackground_5);
	}
}

void BackgroundScroll::Render()
{
	mBackground_1->Render();
	mBackground_2->Render();
	mBackground_2_1->Render();
	mBackground_3->Render();
	mBackground_3_1->Render();
	mBackground_4->Render();
	mBackground_4_1->Render();
	mBackground_5->Render();
	mBackground_5_1->Render();
}
