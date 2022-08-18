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

#define FONT 2 // 総使用フォント数
#define FONT_BBBOcelot 0 // フォント番号
#define FONT_PixelMplus 1
#define COLOR 2 // 総使用フォントカラー数
#define BLACK 0
#define BLUE 1

#define ENEMIES 1

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
	void AddEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& filename);

	// Actorオブジェクト取得
	class Player* GetPlayer() { return mPlayer; }
	class Mob* GetMob() { return mMob; }
	class Friend* GetFriend() { return mFriend; }
	std::vector<class Object*> GetObject() { return mObject; }
	std::vector<class Vector2> GetObjPosition() const{ return objPosition; }
private:
	// ゲーム処理
	void ProcessInput();
	// ゲーム更新
	void UpdateGame();
	// ゲーム描画
	void GenerateOutput();
	// テキストレンダラ
	// 呼び出し前に、txtRectとpasteRectを初期化しておく必要がある
	void RenderText(int font,int color,const char*text, int rw,int rh );
	// bufの一部文字列を表示させる
	void DispTextfile(int font, int color, int rw, int rh);

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
	TTF_Font* mFont[FONT];
	// フォントカラー
	SDL_Color mColor[COLOR];
	//SDL_Surface* mSurface[3];
	//SDL_Texture* mTexture[3];

	SDL_Rect txtRect, pasteRect;
	// ファイルポインタ
	FILE* fp;
	// 文字列バッファ
	char buf[1024];
	int bufCount;
	int iw, ih;

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
	class Friend* mFriend;
	class Mob* mMob;
	class Goal* mGoal;
	std::vector<class Object*> mObject;
	std::vector<class Enemy*> mEnemy;
	class Sprite* timerBackground;

	// Objectの座標配列
	std::vector<class Vector2> objPosition;
	
	class MakeDangeon* dangeon;
};
