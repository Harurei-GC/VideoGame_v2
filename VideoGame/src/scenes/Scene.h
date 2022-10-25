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

// 総使用フォント数はGame.hに定義されています
#define FONT_BBBOcelot_Regular 0 // フォント番号
#define FONT_PixelMplus 1
#define FONT_BBB_Simulator_Black 2

#define COLOR 4 // 総使用フォントカラー数
#define BLACK 0// HACK:#define BLACK {0,0,0,255}のように直接指定した方がいい
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
		virtual void Start();	// 各シーンのRunLoopが始まる直前に1回実行
		virtual void ProcessInput();
		virtual void UpdateGame();
		virtual void GenerateOutput(){}

		// @todo sceneの派生クラスで、ポインタ配列を保持しているものは、デストラクタで消去が出来ているかどうかを確認する。加えて、Add,Removeが作成されており、対象クラスのコンストラクタ・デストラクタでAdd,Removeが呼び出されているか確認する。
		void AddActor(class actors::Actor* actor);
		void RemoveActor(class actors::Actor* actor);
		void AddSprite(class components::SpriteComponent* sprite);
		void RemoveSprite(class components::SpriteComponent* sprite);
		// Visitorクラスをインスタンス化したときに自動で呼び出される
		void AddVisitor(visitors::Visitor* visitor) ;
		void RemoveVisitor(visitors::Visitor* visitor) ;
		// @note BlockTreeはBattleクラスで実装
		virtual void AddBlockTree(class actors::background::BlockTree* block) {};
		virtual void RemoveBlockTree(class actors::background::BlockTree* block) {};

		game::Game* GetGame() { return mGame; }
		bool GetIsRunning() { return mIsRunning; }
		void SetIsRunning(bool run) { mIsRunning = run; }
		SDL_Texture* GetTexture(const std::string& filename);


		// NOTE:呼び出し前に、txtRectとpasteRectを初期化しておく必要がある
		void RenderText(int font, int color, const char* text, int rw, int rh);
		// bufの一部文字列を表示させる
		void DispSentenceFromFile(int font, int color, int rw, int rh);

	protected:

		// オーバーライドしたのち派生クラスのコンストラクタで呼び出す。
		// オーバーライドするときは、必ず基底クラスの仮想関数を一緒に呼ぶ。
		// （ScnGameStart::ReadTextFileを参考に）
		// Sceneごとに読み込むテキストファイルを変える
		void ReadTextFile(const char* file);

		game::Game* mGame;
		bool mIsRunning;
		bool mUpdatingActors;
		std::vector<actors::Actor*> mActors;
		std::vector<actors::Actor*> mPendingActors;
		std::vector<class components::SpriteComponent*>mSprites;
		std::vector<class visitors::Visitor*>mVisitors;


		// 文字列表示に使う
		char buf[1024];
		FILE* fp;
		int texW, texH;
		int bufCount;

		float deltaTime;
	private:

		std::unordered_map<std::string, SDL_Texture*> mTextures;
		SDL_Color mColor[COLOR];
		SDL_Rect txtRect, pasteRect;

	};
}
