#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL_ttf.h"
#include <map>

#define FONT 2 // ���g�p�t�H���g��

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

	// Actor�I�u�W�F�N�g�擾
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
	// �e�L�X�g�����_��
	// �Ăяo���O�ɁAtxtRect��pasteRect�����������Ă����K�v������
	//void RenderText(int font,int color,const char*text, int rw,int rh );
	// buf�̈ꕔ�������\��������
	//void DispTextfile(int font, int color, int rw, int rh);

	//void GameStart();
	//void GameClear();
	//void GameOver();
	
	void LoadData();
	void UnloadScene();
	//void UnloadData();
	// �������ԉ߂�����
	bool isTimeOut(float deltaTime);

	//std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �Q�[���E�C���h�E
	SDL_Window* mWindow;


	std::vector<class Scene*> mScenes;

	float timeLimit;
	bool quitGame;
	//// �����񃌃��_��
	//// �t�H���g�J���[
	//SDL_Color mColor[COLOR];
	//SDL_Surface* mSurface[3];
	//SDL_Texture* mTexture[3];

	//SDL_Rect txtRect, pasteRect;
	//// �t�@�C���|�C���^
	//FILE* fp;
	// ������o�b�t�@
	//char buf[1024];
	//int bufCount;
	//int iw, ih;

	//// �Q�[���ɓo�ꂷ�邷�ׂĂ�Actor
	//std::vector<class Actor*> mActors;
	//// �ۗ�����Actor
	//std::vector<class Actor*> mPendingActors;
	// SpriteComponent
	//std::vector<class SpriteComponent*> mSprites;

	// ���ׂ�Scene���t���O���Ǘ�����
	//bool mIsStart;
	//bool mIsRunning;
	bool mIsCleared;
	bool mIsOver;
	//bool mUpdatingActors;

	//// ������ւ�S��Scene�ŊǗ�
	//class Player* mPlayer;
	//class Friend* mFriend;
	//class Mob* mMob;
	//class Goal* mGoal;
	//std::vector<class Object*> mObject;
	// NOTE:�L�[-1�ɋ��Enemy����
	//std::map<int ,class Enemy*> mEnemy;
	//class Sprite* timerBackground;

	// Object�̍��W�z��
	//std::vector<class Vector2> objPosition;
	
	////class MakeDangeon* dangeon;
	//class ConfigureMovementStatus* configMoveStatus;

};
