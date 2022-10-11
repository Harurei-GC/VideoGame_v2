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

#define FONT_BBBOcelot 0 // �t�H���g�ԍ�
#define FONT_PixelMplus 1
#define COLOR 3 // ���g�p�t�H���g�J���[��
// HACK:#define BLACK {0,0,0,255}�̂悤�ɒ��ڎw�肵����������
#define BLACK 0
#define BLUE 1
#define RED 2


namespace scenes
{
	class Scene
	{
	public:
		Scene(game::Game* game);
		~Scene();
		void RunLoop();
		virtual void Start() {}
		virtual void ProcessInput() {}
		virtual void UpdateGame() {}
		virtual void GenerateOutput() {}

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
		SDL_Texture* GetTexture(const std::string& filename);


		// NOTE:�Ăяo���O�ɁAtxtRect��pasteRect�����������Ă����K�v������
		void RenderText(int font, int color, const char* text, int rw, int rh);

	protected:
		game::Game* mGame;
		bool mIsRunning;
		bool mUpdatingActors;
		int texW, texH;
		std::vector<actors::Actor*> mActors;
		std::vector<actors::Actor*> mPendingActors;
		std::vector<class components::SpriteComponent*>mSprites;
		std::vector<class visitors::Visitor*>mVisitors;

	private:

		std::unordered_map<std::string, SDL_Texture*> mTextures;
		SDL_Color mColor[COLOR];
		SDL_Rect txtRect, pasteRect;

	};
}
