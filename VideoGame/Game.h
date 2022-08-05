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
#define W_BOXES 32 // �������̃}�X�ڂ̐�
#define H_BOXES 24 // �c�����̃}�X�ڂ̐�

// �Q�[���̋N���A�I���ȂǊǗ�
class Game 
{
public:
	Game();
	// �Q�[���̏�����
	// �E�C���h�E�̍쐬�⃉�C�u�����̏��������s��
	// �������ɐ��������true,���s��false��Ԃ�
	bool Initialize();
	// �Q�[���Ń��[�v���郁�\�b�h���L�q
	void RunLoop();
	// �Q�[���̏I��
	void Shutdown();

	void AddObject(class Object* object);
	void RemoveObject(class Object* object);
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& filename);

	// Actor�I�u�W�F�N�g�擾
	class Player* GetPlayer() { return mPlayer; }
	class Mob* GetMob() { return mMob; }
	std::vector<class Object*> GetObject() { return mObject; }
	std::vector<class Vector2> GetObjPosition() const{ return objPosition; }
private:
	// �Q�[������
	void ProcessInput();
	// �Q�[���X�V
	void UpdateGame();
	// �Q�[���`��
	void GenerateOutput();

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
	TTF_Font* mFontTimer;
	TTF_Font* mFontStr;
	// �t�H���g�J���[
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
	// ����Actor���X�V���Ă��邩
	bool mUpdatingActors;

	// Actor�I�u�W�F�N�g
	class Player* mPlayer;
	class Mob* mMob;
	class Goal* mGoal;
	std::vector<class Object*> mObject;

	// Object�̍��W�z��
	std::vector<class Vector2> objPosition;
	
	class MakeDangeon* dangeon;
};
