#pragma once
#include "game/Game.h"
#include "actors/Actor.h"
#include <vector>
#include "SDL_image.h"
#include "visitors/Visitor.h"

namespace visitors
{ 
	class Visitor;
	class VisitorGetPositions;
}
namespace game
{
	class Game;
}
namespace actors
{
	class Actor;
	namespace background
	{
		class BlockTree;
	}
}
namespace components
{
	class SpriteComponent;
}

#define WIDTH 1024.0f
#define HEIGHT 768.0f
#define SCREEN_OUT_SPEED 360.0f
#define CHARACHIP_EDGE 32.0f

// ���g�p�t�H���g����Game.h�ɒ�`����Ă��܂�
#define FONT_BBBOcelot_Regular 0 // �t�H���g�ԍ�
#define FONT_PixelMplus 1
#define FONT_BBB_Simulator_Black 2

#define COLOR 4 // ���g�p�t�H���g�J���[��
#define BLACK 0// HACK:#define BLACK {0,0,0,255}�̂悤�ɒ��ڎw�肵����������
#define BLUE 1
#define RED 2
#define YELLOW 3


namespace scenes
{
	class Scene
	{
	public:
		Scene(game::Game* game);
		~Scene();
		void RunLoop();
		virtual void Start();	// �e�V�[����RunLoop���n�܂钼�O��1����s
		virtual void ProcessInput();
		virtual void UpdateGame();
		virtual void GenerateOutput(){}

		// @todo scene�̔h���N���X�ŁA�|�C���^�z���ێ����Ă�����̂́A�f�X�g���N�^�ŏ������o���Ă��邩�ǂ������m�F����B�����āAAdd,Remove���쐬����Ă���A�ΏۃN���X�̃R���X�g���N�^�E�f�X�g���N�^��Add,Remove���Ăяo����Ă��邩�m�F����B
		void AddActor(class actors::Actor* actor);
		void RemoveActor(class actors::Actor* actor);
		void AddSprite(class components::SpriteComponent* sprite);
		void RemoveSprite(class components::SpriteComponent* sprite);
		// Visitor�N���X���C���X�^���X�������Ƃ��Ɏ����ŌĂяo�����
		void AddVisitor(visitors::Visitor* visitor) ;
		void RemoveVisitor(visitors::Visitor* visitor) ;
		// @note BlockTree��Battle�N���X�Ŏ���
		virtual void AddBlockTree(class actors::background::BlockTree* block) {};
		virtual void RemoveBlockTree(class actors::background::BlockTree* block) {};

		game::Game* GetGame() { return mGame; }
		bool GetIsRunning() { return mIsRunning; }
		void SetIsRunning(bool run) { mIsRunning = run; }
		SDL_Texture* GetTexture(const std::string& filename);


		// NOTE:�Ăяo���O�ɁAtxtRect��pasteRect�����������Ă����K�v������
		void RenderText(int font, int color, const char* text, int rw, int rh);
		// buf�̈ꕔ�������\��������
		void DispSentenceFromFile(int font, int color, int rw, int rh);

	protected:

		// �I�[�o�[���C�h�����̂��h���N���X�̃R���X�g���N�^�ŌĂяo���B
		// �I�[�o�[���C�h����Ƃ��́A�K�����N���X�̉��z�֐����ꏏ�ɌĂԁB
		// �iScnGameStart::ReadTextFile���Q�l�Ɂj
		// Scene���Ƃɓǂݍ��ރe�L�X�g�t�@�C����ς���
		void ReadTextFile(const char* file);

		game::Game* mGame;
		bool mIsRunning;
		bool mUpdatingActors;
		int texW, texH;
		std::vector<actors::Actor*> mActors;
		std::vector<actors::Actor*> mPendingActors;
		std::vector<class components::SpriteComponent*>mSprites;
		std::vector<class visitors::Visitor*>mVisitors;

		// ������\���Ɏg��
		int bufCount;
		char buf[1024];
		FILE* fp;

		float deltaTime;
	private:

		std::unordered_map<std::string, SDL_Texture*> mTextures;
		SDL_Color mColor[COLOR];
		SDL_Rect txtRect, pasteRect;

	};
}
