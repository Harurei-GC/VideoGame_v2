#include "scenes/Scene.h"
#include "visitors/Visitor.h"
#include "components/SpriteComponent.h"

namespace scenes
{
	Scene::Scene(game::Game* game)
		:mIsRunning(true)
		, mGame(game)
		, mUpdatingActors(false)
	{
		mColor[BLACK] = { 0,0,0,255 };
		mColor[BLUE] = { 30, 30, 240, 255 };
		mColor[RED] = { 240, 50, 50, 255 };

		game->AddScene(this);
	}


	Scene::~Scene()
	{
		while (!mActors.empty())
		{
			delete mActors.back();
		}
		while (!mPendingActors.empty())
		{
			delete mPendingActors.back();
		}
		while (!mSprites.empty())
		{
			delete mSprites.back();
		}
		while (!mVisitors.empty())
		{
			delete mVisitors.back();
		}

		mGame->RemoveScene(this);
	}

	// NOTE:”h¶ƒNƒ‰ƒX‚É‚¨‚¢‚ÄUpdateGame()‚È‚Ç‚ÌoverrideŠÖ”‚ð“Ç‚Ýž‚Þ‚æ‚¤‚É‚µ‚½‚¢
	void Scene::RunLoop()
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

	void Scene::AddActor(actors::Actor* actor)
	{
		if (mUpdatingActors)
		{
			mPendingActors.emplace_back(actor);
		}
		else
		{
			mActors.emplace_back(actor);
		}
	}

	void Scene::RemoveActor(actors::Actor* actor)
	{
		auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
		if (iter != mPendingActors.end())
		{
			std::iter_swap(iter, mPendingActors.end() - 1);
			mPendingActors.pop_back();
		}

		iter = std::find(mActors.begin(), mActors.end(), actor);
		if (iter != mActors.end())
		{
			std::iter_swap(iter, mActors.end() - 1);
			mActors.pop_back();
		}
	}

	void Scene::AddSprite(components::SpriteComponent* sprite)
	{
		int myDrawOrder = sprite->GetDrawOrder();
		auto iter = mSprites.begin();
		for (; iter != mSprites.end(); iter++)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}
		mSprites.insert(iter, sprite);
	}

	void Scene::RemoveSprite(components::SpriteComponent* sprite)
	{
		auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
		if (iter != mSprites.end())
		{
			std::iter_swap(iter, mSprites.end() - 1);
			mSprites.pop_back();
		}
	}


	void Scene::AddVisitor(visitors::Visitor* visitor)
	{
		mVisitors.emplace_back(visitor);
	}

	void Scene::RemoveVisitor(visitors::Visitor* visitor)
	{
		auto iter = std::find(mVisitors.begin(), mVisitors.end(), visitor);
		if (iter != mVisitors.end())
		{
			mVisitors.erase(iter);
		}
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

}
