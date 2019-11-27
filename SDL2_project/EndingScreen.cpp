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
	mTop10 = new Texture("Top 10", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });

	mTop10->Parent(mMiddleBar);

	mTop10->Pos(Vector2D(0.0f, 0.0f));

	mMiddleBar->Parent(this);

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.75f));
	mCredit = new Texture("Credit", Graphics::Instance()->FONT_Emulogic, 36, { 200, 0, 0 });
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
	delete mTop10;
	mTop10 = nullptr;

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

void EndingScreen::Update()
{
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
	mTop10->Render();

	//Render Bottom Bar Entities
	mCredit->Render();
	mNames->Render();
	mFredrik->Render();
	mGwangyeong->Render();
	mMattias->Render();
}
