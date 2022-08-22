#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL_ttf.h"
#include <map>

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

class Game 
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddObject(class Object* object);
	void RemoveObject(class Object* object);
	void AddEnemy(int key,class Enemy* enemy);
	void RemoveEnemy(int key);
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
	std::map<int,class Enemy*> GetEnemy() const { return mEnemy; }

	template<typename MAP, typename KEY>
	bool ContainsKey(MAP m, KEY k)
	{
		return m.find(k) != m.end();
	}
	class Enemy* GetPersonalEnemy(int key)
	{
		if (ContainsKey(mEnemy, key))
		{
			return mEnemy.at(key);
		}
		else
		{
			return mEnemy.at(-1);
		}
	}
private:
	void ProcessInput();
	void UpdateGame();
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
	bool mUpdatingActors;

	class Player* mPlayer;
	class Friend* mFriend;
	class Mob* mMob;
	class Goal* mGoal;
	std::vector<class Object*> mObject;
	// NOTE:キー-1に空のEnemyあり
	std::map<int ,class Enemy*> mEnemy;
	class Sprite* timerBackground;

	// Objectの座標配列
	std::vector<class Vector2> objPosition;
	
	class MakeDangeon* dangeon;
};
