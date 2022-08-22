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
#define W_BOXES 32 // �������̃}�X�ڂ̐�
#define H_BOXES 24 // �c�����̃}�X�ڂ̐�

#define FONT 2 // ���g�p�t�H���g��
#define FONT_BBBOcelot 0 // �t�H���g�ԍ�
#define FONT_PixelMplus 1
#define COLOR 2 // ���g�p�t�H���g�J���[��
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

	// Actor�I�u�W�F�N�g�擾
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
	// �e�L�X�g�����_��
	// �Ăяo���O�ɁAtxtRect��pasteRect�����������Ă����K�v������
	void RenderText(int font,int color,const char*text, int rw,int rh );
	// buf�̈ꕔ�������\��������
	void DispTextfile(int font, int color, int rw, int rh);

	void GameStart();
	void GameClear();
	void GameOver();
	
	void LoadData();
	void UnloadData();
	// �������ԉ߂�����
	bool isTimeOut(float deltaTime);

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �Q�[���E�C���h�E
	SDL_Window* mWindow;

	// �����񃌃��_��
	TTF_Font* mFont[FONT];
	// �t�H���g�J���[
	SDL_Color mColor[COLOR];
	//SDL_Surface* mSurface[3];
	//SDL_Texture* mTexture[3];

	SDL_Rect txtRect, pasteRect;
	// �t�@�C���|�C���^
	FILE* fp;
	// ������o�b�t�@
	char buf[1024];
	int bufCount;
	int iw, ih;

	// 2D�����_��
	SDL_Renderer* mRenderer;
	// �o�ߎ��ԃJ�E���g
	uint32_t mTicksCount;
	// ��������
	float timeLimit;
	// �Q�[���ɓo�ꂷ�邷�ׂĂ�Actor
	std::vector<class Actor*> mActors;
	// �ۗ�����Actor
	std::vector<class Actor*> mPendingActors;
	// SpriteComponent
	std::vector<class SpriteComponent*> mSprites;
	// �X�^�[�g��ʂ��ǂ���
	bool mIsStart;
	// �Q�[���������Ă��邩�ǂ����Btrue�ł������RunLoop�֐��͎��s��������
	bool mIsRunning;
	// �N���A������
	bool mIsCleared;
	// ���Ԑ؂ꂩ
	bool mIsOver;
	bool mUpdatingActors;

	class Player* mPlayer;
	class Friend* mFriend;
	class Mob* mMob;
	class Goal* mGoal;
	std::vector<class Object*> mObject;
	// NOTE:�L�[-1�ɋ��Enemy����
	std::map<int ,class Enemy*> mEnemy;
	class Sprite* timerBackground;

	// Object�̍��W�z��
	std::vector<class Vector2> objPosition;
	
	class MakeDangeon* dangeon;
};
