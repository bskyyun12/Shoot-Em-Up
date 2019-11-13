#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Graphics();
	}
	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = nullptr;

	sInitialized = false;
}

bool Graphics::Initialized() {

	return sInitialized;
}

Graphics::Graphics()
{
	sInitialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError());
		Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr)
	{
		printf("Window Creation Error: %s\n", SDL_GetError());
		Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		printf("IMG Initialization Error: %s\n", IMG_GetError());
		Logger::Log(IMG_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF Initialization Error: %s\n", TTF_GetError());
		Logger::Log(TTF_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = nullptr;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == nullptr)
	{
		printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		Logger::Log(IMG_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return nullptr;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, tempSurface);
	if (tex == nullptr)
	{
		printf("Create Texture Error: %s\n", SDL_GetError());
		Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return nullptr;
	}

	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (tempSurface == nullptr)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		Logger::Log(TTF_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, tempSurface);
	if (tex == nullptr)
	{
		printf("Text Texture Creation Error: %s\n", SDL_GetError());
		Logger::Log(SDL_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
		return nullptr;
	}

	SDL_FreeSurface(tempSurface);

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}
