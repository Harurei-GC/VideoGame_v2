#pragma once
#include "../Game.h"
#include "../actors/Actor.h"
#include <vector>
#include "SDL_image.h"

#define WIDTH 1024.0f
#define HEIGHT 768.0f
#define SCREEN_OUT_SPEED 360.0f
#define CHARACHIP_EDGE 32.0f

#define FONT_BBBOcelot 0 // フォント番号
#define FONT_PixelMplus 1
#define COLOR 2 // 総使用フォントカラー数
#define BLACK 0
#define BLUE 1

#define ENEMIES 1

class Scene
{
public:
	Scene(Game* game);
	~Scene();
	void RunLoop();
	// DANGER:クラスのStartと同名
	virtual void Start(){};
	virtual void ProcessInput(){}
	virtual void UpdateGame(){}
	virtual void GenerateOutput(){}

	virtual void AddActor(Actor* actor){};
	virtual void RemoveActor(Actor* actor){};
	virtual void AddEnemy(int id, class Enemy* enemy){};
	virtual void RemoveEnemy(int id){};
	virtual void AddObject(class Object* object){};
	virtual void RemoveObject(class Object* object){};
	virtual void AddSprite(class SpriteComponent* sprite){};
	virtual void RemoveSprite(class SpriteComponent* sprite){};
	
	//virtual std::vector<class Object*> GetObject() { return; }
	//virtual std::vector<class Vector2> GetObjPosition()const { return; }
	//virtual std::map<int, class Enemy*> GetEnemy() const { return; }
	Game* GetGame() { return mGame; }
	bool GetIsRunning() { return mIsRunning; }
	SDL_Texture* GetTexture(const std::string& filename);

	
	// NOTE:呼び出し前に、txtRectとpasteRectを初期化しておく必要がある
	void RenderText(int font, int color, const char* text, int rw, int rh);


	// bufの一部文字列を表示させる
	void DispTextfile(int font, int color, int rw, int rh);
protected:
	Game* mGame;
	bool mIsRunning;

	// HACK:RenderText()内で使用する変数群。
	// 問題点については下記参考
	//SDL_Renderer* mRenderer;
	int texW, texH;
private:
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// RenderText()内で使用する変数群
	// HACK:Sceneクラスか、派生クラスか、Gameクラスか、どれで保持するか考える
	//TTF_Font* mFont[FONT];
	SDL_Color mColor[COLOR];
	SDL_Rect txtRect, pasteRect;
};
