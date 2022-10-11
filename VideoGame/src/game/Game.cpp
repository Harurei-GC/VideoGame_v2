// GameManagerのような役割
// Sceneクラスを作成し管理する（ポインタではない普通の宣言）
// ゲームの記述は行わない

#include "game/Game.h"
#include "SDL_image.h"
#include "actors/Actor.h"
#include "components/SpriteComponent.h"
#include <iostream>
#include "actors/characters/Player.h"
#include "actors/characters/MBox.h"
#include "actors/background/BlockTree.h"
#include "actors/background/Goal.h"
#include "SDL_ttf.h"
#include "managers/MakeDangeon.h"
#include "math/Random.h"
#include "actors/characters/Enemy.h"
#include "actors/characters/Friend.h"
#include "actors/background/Sprite.h"
#include "scenes/GameStart.h"
#include "scenes/Battle.h"
#include "scenes/GameClear.h"
#include "scenes/GameOver.h"
#include "scenes/Scene.h"


namespace game
{
	Game::Game()
		:mWindow(nullptr)
		, mIsCleared(false)
		, mIsOver(false)
		, quitGame(false)
	{
	}

	bool Game::Initialize()
	{
		// SDLライブラリ初期化
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// ウィンドウ作成(タイトル)
		mWindow = SDL_CreateWindow("Video Game", 100, 100, WIDTH, HEIGHT, 0);
		if (!mWindow)
		{
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return false;
		}

		// 2Dレンダリングコンテキスト作成
		gameRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!gameRenderer)
		{
			SDL_Log("Failed to create renderer: %s", SDL_GetError());
			return false;
		}

		// 画像形式読み込めるようにする
		if (IMG_Init(IMG_INIT_PNG) == 0)
		{
			SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
			return false;
		}

		// TTFライブラリ初期化
		if (TTF_Init() == -1)
		{
			SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
		}


		LoadData();

		mTicksCount = SDL_GetTicks();

		return true;
	}


	// 各シーンに必要なものを持っていく
	void Game::LoadData()
	{
		mFont[FONT_BBBOcelot] = TTF_OpenFont("font/bbbixxxel/04_Brischke/BBBOcelot-Regular.otf", 24);
		if (!mFont[FONT_BBBOcelot])
		{
			std::cout << "Failed to get font for timer" << std::endl;
		}
		mFont[FONT_PixelMplus] = TTF_OpenFont("font/PixelMplus-20130602/PixelMplus12-Regular.ttf", 24);
		if (!mFont[FONT_PixelMplus])
		{
			std::cout << "Failed to get font for timer" << std::endl;
		}

		// TODO:Sceneの追加
		gameStart = new scenes::GameStart(this);
		battle = new scenes::Battle(this);
		gameClear = new scenes::GameClear(this);
		gameOver = new scenes::GameOver(this);

		// Start()を実行したいときはここに入れる 
		gameStart->Start();
		battle->Start();
		gameClear->Start();
		gameOver->Start();
	}


	void Game::RunLoop()
	{
		// 各シーンへの遷移
		while (gameStart->GetIsRunning())
		{
			gameStart->RunLoop();
		}
		if (quitGame)
		{
			return;
		}
		while (battle->GetIsRunning())
		{
			battle->RunLoop();
		}
		if (quitGame)
		{
			return;
		}
		if (mIsCleared)
		{
			while (gameClear->GetIsRunning())
			{
				gameClear->RunLoop();
			}
		}
		if (quitGame) { return; }
		if (mIsOver)
		{
			while (gameOver->GetIsRunning())
			{
				gameOver->RunLoop();
			}
		}

	}

	void Game::Shutdown()
	{
		IMG_Quit();
		SDL_DestroyRenderer(gameRenderer);
		SDL_DestroyWindow(mWindow);
		for (int i = 0; i < FONT; i++) // iはmFontの要素数
		{
			TTF_CloseFont(mFont[i]);
		}
		TTF_Quit();
		SDL_Quit();
	}


	void Game::AddScene(scenes::Scene* scene)
	{
		mScenes.emplace_back(scene);
	}

	void Game::RemoveScene(scenes::Scene* scene)
	{
		auto iter = std::find(mScenes.begin(), mScenes.end(), scene);
		if (iter != mScenes.end())
		{
			std::iter_swap(iter, mScenes.end() - 1);
			mScenes.pop_back();
		}
	}

}