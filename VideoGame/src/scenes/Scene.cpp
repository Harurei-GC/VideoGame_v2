#include "Scene.h"

Scene::Scene(Game* game)
	:mIsRunning(true)
	,mGame(game)
	, mUpdatingActors(false)
{
	mColor[BLACK] = { 0,0,0,255 };
	mColor[BLUE] = { 30, 30, 240, 255 };
	mColor[RED] = { 240, 50, 50, 255 };

	game->AddScene(this);
}


Scene::~Scene()
{
	mGame->RemoveScene(this);
}

// NOTE:”h¶ƒNƒ‰ƒX‚É‚¨‚¢‚ÄUpdateGame()‚È‚Ç‚ÌoverrideŠÖ”‚ð“Ç‚Ýž‚Þ‚æ‚¤‚É‚µ‚½‚¢
void Scene::RunLoop()
{
	ProcessInput();
	UpdateGame();
	GenerateOutput();
}

SDL_Texture* Scene::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* img = IMG_Load(filename.c_str());
		if (!img)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}
		tex = SDL_CreateTextureFromSurface(mGame->gameRenderer, img);
		SDL_FreeSurface(img);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
			return nullptr;
		}
		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}


void Scene::RenderText(int font, int color, const char* text, int rw, int rh)
{
	SDL_Surface* surf = TTF_RenderUTF8_Blended(mGame->mFont[font], text, mColor[color]);
	SDL_Texture* txtr = SDL_CreateTextureFromSurface(mGame->gameRenderer, surf);
	SDL_QueryTexture(txtr, NULL, NULL, &texW, &texH);
	txtRect = SDL_Rect{ 0,0,texW,texH };
	pasteRect = SDL_Rect{ rw,rh,texW,texH };
	SDL_RenderCopy(mGame->gameRenderer, txtr, &txtRect, &pasteRect);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(txtr);
}

