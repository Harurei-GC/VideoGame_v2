#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL_ttf.h"
#include <map>

#define FONT 2 // 総使用フォント数

class Game 
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddScene(class Scene* scene);
	void RemoveScene(class Scene* scene);

	void SetQuitGame(bool quit) { quitGame = quit; }
	void SetGameClear(bool clear) { mIsCleared = clear; }
	void SetGameOver(bool over) { mIsOver = over; }

	SDL_Renderer* gameRenderer;
	uint32_t mTicksCount;
	TTF_Font* mFont[FONT];

	class Start* start;
	class Battle* battle;
	class GameClear* gameClear;
	class GameOver* gameOver;
private:
	void LoadData();
	bool isTimeOut(float deltaTime);

	// ゲームウインドウ
	SDL_Window* mWindow;


	std::vector<class Scene*> mScenes;

	float timeLimit;
	bool quitGame;

	bool mIsCleared;
	bool mIsOver;

};
