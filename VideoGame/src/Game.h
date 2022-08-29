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

	//void AddObject(class Object* object);
	//void RemoveObject(class Object* object);
	//void AddEnemy(int key,class Enemy* enemy);
	//void RemoveEnemy(int key);
	//void AddActor(class Actor* actor);
	//void RemoveActor(class Actor* actor);
	//void AddSprite(class SpriteComponent* sprite);
	//void RemoveSprite(class SpriteComponent* sprite);
	void AddScene(class Scene* scene);

	//SDL_Texture* GetTexture(const std::string& filename);

	// Actorオブジェクト取得
	//class Player* GetPlayer() { return mPlayer; }
	//class Mob* GetMob() { return mMob; }
	//class Friend* GetFriend() { return mFriend; }
	//std::vector<class Object*> GetObject() { return mObject; }
	////std::vector<class Vector2> GetObjPosition() const{ return objPosition; }
	//std::map<int,class Enemy*> GetEnemy() const { return mEnemy; }


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
	//void ProcessInput();
	//void UpdateGame();
	//void GenerateOutput();
	// テキストレンダラ
	// 呼び出し前に、txtRectとpasteRectを初期化しておく必要がある
	//void RenderText(int font,int color,const char*text, int rw,int rh );
	// bufの一部文字列を表示させる
	//void DispTextfile(int font, int color, int rw, int rh);

	//void GameStart();
	//void GameClear();
	//void GameOver();
	
	void LoadData();
	void UnloadScene();
	//void UnloadData();
	// 制限時間過ぎたか
	bool isTimeOut(float deltaTime);

	//std::unordered_map<std::string, SDL_Texture*> mTextures;

	// ゲームウインドウ
	SDL_Window* mWindow;


	std::vector<class Scene*> mScenes;

	float timeLimit;
	bool quitGame;
	//// 文字列レンダラ
	//// フォントカラー
	//SDL_Color mColor[COLOR];
	//SDL_Surface* mSurface[3];
	//SDL_Texture* mTexture[3];

	//SDL_Rect txtRect, pasteRect;
	//// ファイルポインタ
	//FILE* fp;
	// 文字列バッファ
	//char buf[1024];
	//int bufCount;
	//int iw, ih;

	//// ゲームに登場するすべてのActor
	//std::vector<class Actor*> mActors;
	//// 保留中のActor
	//std::vector<class Actor*> mPendingActors;
	// SpriteComponent
	//std::vector<class SpriteComponent*> mSprites;

	// すべてSceneがフラグを管理する
	//bool mIsStart;
	//bool mIsRunning;
	bool mIsCleared;
	bool mIsOver;
	//bool mUpdatingActors;

	//// ここらへん全部Sceneで管理
	//class Player* mPlayer;
	//class Friend* mFriend;
	//class Mob* mMob;
	//class Goal* mGoal;
	//std::vector<class Object*> mObject;
	// NOTE:キー-1に空のEnemyあり
	//std::map<int ,class Enemy*> mEnemy;
	//class Sprite* timerBackground;

	// Objectの座標配列
	//std::vector<class Vector2> objPosition;
	
	////class MakeDangeon* dangeon;
	//class ConfigureMovementStatus* configMoveStatus;

};
