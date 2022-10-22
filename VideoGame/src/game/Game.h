#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "math/Math.h"
#include "SDL_ttf.h"
#include <map>

#define FONT 3 // 総使用フォント数

namespace scenes
{
	class Scene;
	class ScnGameStart;
	class ScnBattle;
	class ScnGameOver;
	class ScnGameClear;
	class ScnKeyConfig;
}
namespace data
{
	class KeyData;
}

namespace game
{
	class Game
	{
	public:
		Game();
		bool Initialize();
		void RunLoop();
		void Shutdown();

		void AddScene(class scenes::Scene* scene);
		void RemoveScene(class scenes::Scene* scene);

		void SetQuitGame(bool quit) { quitGame = quit; }
		void SetPlayAgain(bool again) { mPlayAgain = again; }
		void SetGameClear(bool clear) { mIsCleared = clear; }
		void SetGameOver(bool over) { mIsOver = over; }
		void SetKeyConfig(bool key) { mIsKConfig = key; }

		data::KeyData* GetKeyData() { return mKeyData; }

		SDL_Renderer* gameRenderer;
		uint32_t mTicksCount;
		TTF_Font* mFont[FONT];

		scenes::ScnGameStart* gameStart;
		scenes::ScnBattle* battle;
		scenes::ScnGameClear* gameClear;
		scenes::ScnGameOver* gameOver;
		scenes::ScnKeyConfig* keyConfig;

	private:
		void LoadData();
		bool isTimeOut(float deltaTime);
		void RNLP_IsKConfig();
		void RNLP_PlayAgain();
		void RNLP_BattleReset();

		// ゲームウインドウ
		SDL_Window* mWindow;
		data::KeyData* mKeyData;

		std::vector<class scenes::Scene*> mScenes;

		float timeLimit;
		bool quitGame;
		bool mIsKConfig;
		bool mPlayAgain;
		bool mIsCleared;
		bool mIsOver;
	};
}