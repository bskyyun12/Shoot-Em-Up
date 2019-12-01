#include "EndingScreen.h"

EndingScreen::EndingScreen()
{
	mBackgroundScroll = new BackgroundScroll();
	mBackgroundScroll->SetBackground("Backgrounds/space/Nebula_Red", 5);

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mScoreBoard = ScoreBoard::Instance();

	//Middle Bar Entities
	mMiddleBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.2f));
	mTop7 = new Texture("Top 7", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mTop7->Parent(mMiddleBar);
	mTop7->Pos(Vector2D(0.0f, 0.0f));

	mMiddleBar->Parent(this);

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.75f));
	mCredit = new Texture("Credits", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
	mNames = new Texture("Fredrik Gwangyeong Mattias", Graphics::Instance()->FONT_Emulogic, 32, { 230, 230, 230 });
	mFredrik = new AnimatedTexture("Pixel Adventure/Main Characters/Virtual Guy/Run (32x32).png", 0, 0, 32, 32, 12, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mGwangyeong = new AnimatedTexture("Pixel Adventure/Main Characters/Pink Man/Run (32x32).png", 0, 0, 32, 32, 12, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mMattias = new AnimatedTexture("Pixel Adventure/Main Characters/Ninja Frog/Run (32x32).png", 0, 0, 32, 32, 12, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);

	mCredit->Parent(mBottomBar);
	mNames->Parent(mBottomBar);
	mFredrik->Parent(mBottomBar);
	mGwangyeong->Parent(mBottomBar);
	mMattias->Parent(mBottomBar);

	mFredrik->Scale(VECTOR2D_ONE * 2);
	mGwangyeong->Scale(VECTOR2D_ONE * 2);
	mMattias->Scale(VECTOR2D_ONE * 2);

	mCredit->Pos(Vector2D(0.0f, 0.0f));
	mNames->Pos(Vector2D(0.0f, 70.0f));
	mFredrik->Pos(Vector2D(-300.0f, 150.0f));
	mGwangyeong->Pos(Vector2D(0.0f, 150.0f));
	mMattias->Pos(Vector2D(300.0f, 150.0f));

	mBottomBar->Parent(this);

	mHighScoreUpdate = false;
}

EndingScreen::~EndingScreen()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;
	mScoreBoard = nullptr;

	//Freeing Middle Bar Entities
	delete mMiddleBar;
	mMiddleBar = nullptr;
	delete mTop7;
	mTop7 = nullptr;

	for (int i = 0; i < mRanks.size(); i++)
	{
		delete mRanks[i];
		mRanks[i] = nullptr;
	}
	mRanks.clear();

	delete mTmpTexture;
	mTmpTexture = nullptr;

	//Freeing Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mCredit;
	mCredit = nullptr;
	delete mNames;
	mNames = nullptr;
	delete mFredrik;
	mFredrik = nullptr;
	delete mGwangyeong;
	mGwangyeong = nullptr;
	delete mMattias;
	mMattias = nullptr;

	// Background
	delete mBackgroundScroll;
	mBackgroundScroll = nullptr;
}

void EndingScreen::UpdateHighScore()
{
	if (!mHighScoreUpdate)
	{
		for (int i = 0; i < mRanks.size(); i++)
		{
			delete mRanks[i];
			mRanks[i] = nullptr;
		}
		mRanks.clear();

		mScoreBoard->mHighScoreBoard->WriteHighScoreToFile();
		for (int i = 0; i < 7; i++)
		{
			mTmpTexture = new Texture(std::to_string(mScoreBoard->mHighScoreBoard->GetHighScoreAtPosition(i)), Graphics::Instance()->FONT_Emulogic, 36, { 255, 255, 255 });
			mTmpTexture->Parent(mMiddleBar);
			mTmpTexture->Pos(Vector2D(0.0f, (i + 1) * 50.0f));

			std::vector<Texture*>::iterator it;
			it = std::find(mRanks.begin(), mRanks.end(), mTmpTexture);
			// not found
			if (it == mRanks.end())
				mRanks.push_back(mTmpTexture);
		}
		mHighScoreUpdate = true;
	}
}

void EndingScreen::Update()
{
	UpdateHighScore();
	mBackgroundScroll->Update();
	mFredrik->Update();
	mGwangyeong->Update();
	mMattias->Update();
}

void EndingScreen::Render()
{
	// Render background
	mBackgroundScroll->Render();

	//Render Top Bar
	mScoreBoard->Render();

	//Render Middle Bar Entities
	mTop7->Render();
	for (int i = 0; i < mRanks.size(); i++)
	{
		mRanks[i]->Render();
	}

	//Render Bottom Bar Entities
	mCredit->Render();
	mNames->Render();
	mFredrik->Render();
	mGwangyeong->Render();
	mMattias->Render();
}
