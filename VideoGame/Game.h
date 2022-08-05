#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL_ttf.h"

#define WIDTH 1024.0f
#define HEIGHT 768.0f
#define SCREEN_OUT_SPEED 360.0f
#define CHARACHIP_EDGE 32.0f
#define W_BOXES 32 // 横方向のマス目の数
#define H_BOXES 24 // 縦方向のマス目の数

// ゲームの起動、終了など管理
class Game 
{
public:
	Game();
	// ゲームの初期化
	// ウインドウの作成やライブラリの初期化を行う
	// 初期化に成功すればtrue,失敗でfalseを返す
	bool Initialize();
	// ゲームでループするメソッドを記述
	void RunLoop();
	// ゲームの終了
	void Shutdown();

	void AddObject(class Object* object);
	void RemoveObject(class Object* object);
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& filename);

	// Actorオブジェクト取得
	class Player* GetPlayer() { return mPlayer; }
	class Mob* GetMob() { return mMob; }
	std::vector<class Object*> GetObject() { return mObject; }
	std::vector<class Vector2> GetObjPosition() const{ return objPosition; }
private:
	// ゲーム処理
	void ProcessInput();
	// ゲーム更新
	void UpdateGame();
	// ゲーム描画
	void GenerateOutput();

	void GameStart();
	void GameClear();
	void GameOver();
	
	void LoadData();
	void UnloadData();
	// 制限時間過ぎたか
	bool isTimeOut(float deltaTime);

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// ゲームウインドウ
	SDL_Window* mWindow;

	// 文字列レンダラ
	TTF_Font* mFontTimer;
	TTF_Font* mFontStr;
	// フォントカラー
	SDL_Color mColorTimer;
	SDL_Surface* mSurfaceTimer;
	SDL_Texture* mTextureTimer;
	SDL_Rect txtRectTimer, pasteRectTimer;

	SDL_Color mColorStr;
	SDL_Surface* mSurfaceStr;
	SDL_Texture* mTextureStr;
	SDL_Rect txtRectStr, pasteRectStr;

	SDL_Event mEvent;
	const char* text;


	// 2Dレンダラ
	SDL_Renderer* mRenderer;
	// 経過時間カウント
	uint32_t mTicksCount;
	// 制限時間
	float timeLimit;
	// ゲームに登場するすべてのActor
	std::vector<class Actor*> mActors;
	// 保留中のActor
	std::vector<class Actor*> mPendingActors;
	// SpriteComponent
	std::vector<class SpriteComponent*> mSprites;
	// スタート画面かどうか
	bool mIsStart;
	// ゲームが動いているかどうか。trueである限りRunLoop関数は実行し続ける
	bool mIsRunning;
	// クリアしたか
	bool mIsCleared;
	// 時間切れか
	bool mIsOver;
	// 現在Actorを更新しているか
	bool mUpdatingActors;

	// Actorオブジェクト
	class Player* mPlayer;
	class Mob* mMob;
	class Goal* mGoal;
	std::vector<class Object*> mObject;

	// Objectの座標配列
	std::vector<class Vector2> objPosition;
	
	class MakeDangeon* dangeon;
};
