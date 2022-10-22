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
#include "scenes/ScnGameStart.h"
#include "scenes/ScnBattle.h"
#include "scenes/ScnGameClear.h"
#include "scenes/ScnGameOver.h"
#include "scenes/Scene.h"
#include "scenes/ScnKeyConfig.h"
#include "data/KeyData.h"


//#define DEBUG_GAME_CPP_


namespace game
{
	Game::Game()
		:mWindow(nullptr)
		, mIsCleared(false)
		, mIsOver(false)
		, quitGame(false)
		, mPlayAgain(false)
		, mIsKConfig(false)
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
		mFont[FONT_BBBOcelot_Regular] = TTF_OpenFont("font/BBBOcelot-Regular.otf", 24);
		if (!mFont[FONT_BBBOcelot_Regular])
		{
			std::cout << "Failed to get font BBBOcelot_Regular" << std::endl;
		}
		mFont[FONT_PixelMplus] = TTF_OpenFont("font/PixelMplus12-Regular.ttf", 24);
		if (!mFont[FONT_PixelMplus])
		{
			std::cout << "Failed to get font PixelMplus" << std::endl;
		}
		mFont[FONT_BBB_Simulator_Black] = TTF_OpenFont("font/BBB_Simulator_Black.otf", 30);
		if (!mFont[FONT_BBB_Simulator_Black])
		{
			std::cout << "Failed to get font for timer" << std::endl;
		}
		// キーコンフィグのデータを保持するクラス
		mKeyData = new data::KeyData();

		// TODO:Sceneの追加
		gameStart = new scenes::ScnGameStart(this);
		battle = new scenes::ScnBattle(this);
		gameClear = new scenes::ScnGameClear(this);
		gameOver = new scenes::ScnGameOver(this);
		keyConfig = new scenes::ScnKeyConfig(this);

	}


	void Game::RunLoop()
	{
		// 各シーンへの遷移
		// スタート
	GOTO_START:
		gameStart->SetIsRunning(true);
		while (gameStart->GetIsRunning())
		{
			gameStart->Start();
			gameStart->RunLoop();
		}
		if (mIsKConfig)
		{
			RNLP_IsKConfig();
			if (quitGame) { return; }
			goto GOTO_START;
		}
		if (quitGame)
		{
			return;
		}

	GOTO_BATTLE:
		// バトル
		while (battle->GetIsRunning())
		{
			battle->Start();
			battle->RunLoop();
#ifdef DEBUG_GAME_CPP_
			mIsCleared = true;
#endif
		}
		if (quitGame)
		{
			return;
		}

	GOTO_CLEAR:
		// ゲームクリア
		if (mIsCleared)
		{
			gameClear->SetIsRunning(true);
			while (gameClear->GetIsRunning())
			{
				gameClear->Start();
				gameClear->RunLoop();
			}
			RNLP_BattleReset();
			mIsCleared = false;
		}
		if (mIsKConfig)
		{
			RNLP_IsKConfig();
			if (quitGame) { return; }
			goto GOTO_START;
		}
		if (mPlayAgain) 
		{
			RNLP_PlayAgain();
			goto GOTO_BATTLE;
		}
		if (quitGame) 
		{
			return;
		}

	GOTO_OVER:
		// ゲーム失敗
		if (mIsOver)
		{
			gameOver->SetIsRunning(true);
			while (gameOver->GetIsRunning())
			{
				gameOver->Start();
				gameOver->RunLoop();
			}
			RNLP_BattleReset();
			mIsOver = false;
		}
		if (mIsKConfig)
		{
			RNLP_IsKConfig();
			if (quitGame) { return; }
			goto GOTO_START;
		}
		if (mPlayAgain)
		{
			RNLP_PlayAgain();
			goto GOTO_BATTLE;
		}
		if (quitGame)
		{
			return;
		}

	}
	void Game::RNLP_BattleReset()
	{
		delete battle;
		battle = new scenes::ScnBattle(this);
	}

	void Game::RNLP_IsKConfig()
	{
		keyConfig->SetIsRunning(true);
		while (keyConfig->GetIsRunning())
		{
			keyConfig->Start();
			keyConfig->RunLoop();
		}
		mIsKConfig = false;
		battle->SetIsRunning(true);

	}

	void Game::RNLP_PlayAgain()
	{
		battle->SetIsRunning(true);
		mPlayAgain = false;
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