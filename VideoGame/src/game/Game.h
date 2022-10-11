#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "math/Math.h"
#include "SDL_ttf.h"
#include <map>

#define FONT 2 // 総使用フォント数

namespace scenes
{
	class Scene;
	class GameStart;
	class Battle;
	class GameOver;
	class GameClear;
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
		void SetGameClear(bool clear) { mIsCleared = clear; }
		void SetGameOver(bool over) { mIsOver = over; }

		SDL_Renderer* gameRenderer;
		uint32_t mTicksCount;
		TTF_Font* mFont[FONT];

		class scenes::GameStart* gameStart;
		class scenes::Battle* battle;
		class scenes::GameClear* gameClear;
		class scenes::GameOver* gameOver;
	private:
		void LoadData();
		bool isTimeOut(float deltaTime);

		// ゲームウインドウ
		SDL_Window* mWindow;

		std::vector<class scenes::Scene*> mScenes;

		float timeLimit;
		bool quitGame;

		bool mIsCleared;
		bool mIsOver;

	};
}