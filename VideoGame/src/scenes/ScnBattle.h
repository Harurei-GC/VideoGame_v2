#pragma once
#include "scenes/Scene.h"
#include "managers/MakeDangeon.h"
#include <map>
#include "visitors/VisitorGetPositions.h"
#include "scenes/ScnGameClear.h"
#include "message/ActorMessage.h"
#include "message/ManagerMessage.h"

namespace visitors
{
	class VisitorGetPositions;
	class Visitor;
}
namespace game{	class Game; }
namespace scenes { 
	class Scene;
}
namespace managers { 
	class ConfigureMovementStatus; 
	class MakeDangeon;
}
namespace actors { 
	class Actor;
	namespace background
	{
		class BlockTree;
		class Goal;
		class Sprite;
	} 
	namespace characters
	{
		class Enemy;
		class Player;
		class MBox;
	}
}
namespace components { class SpriteComponent; }


#define ENEMIES 2
namespace bg = actors::background;
namespace ch = actors::characters;

namespace scenes
{
	class ScnBattle :public Scene
	{
	public:
		ScnBattle(game::Game* game);
		~ScnBattle();
		void Start()override;
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;

		void AddBlockTree(bg::BlockTree* block)override;
		void RemoveBlockTree(bg::BlockTree* block)override;
		std::vector<bg::BlockTree*> GetBlkTree() { return mBlkTree; }
		std::vector<class Vector2> GetBoxPosition()const { return boxPosition; }

		message::ActorMessage* GetActorMessage()override { return &actorMessage; }
		message::ManagerMessage* GetManagerMessage()override { return &managerMessage; }

		std::map<int,ch::Enemy*> GetEnemiesMap() const { return mEnemy; }
		ch::Player* GetPlayer() { return mPlayer; }
		//class Friend* GetFriend() { return mFriend; }
		ch::MBox* GetMBox() { return mMBox; }

		template<typename MAP, typename KEY>
		bool ContainsKey(MAP m, KEY k)
		{
			return m.find(k) != m.end();
		}
		ch::Enemy* GetPersonalEnemy(int key)
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
		bool IsTimeOut(float deltaTime);

		message::ActorMessage actorMessage;
		message::ManagerMessage managerMessage;

		std::map<int, ch::Enemy*> mEnemy;
		//ch::Friend* mFriend;
		ch::MBox* mMBox;
		ch::Player* mPlayer;

		bg::Goal* mGoal;
		bg::Sprite* timerBackground;
		managers::MakeDangeon dangeon;
		managers::ConfigureMovementStatus* configMoveStatus;
		visitors::VisitorGetPositions* vstGetPos;
		float timeLimit;
		Score mScore;

		std::vector<class Vector2> boxPosition;
		std::vector<bg::BlockTree*> mBlkTree;
	};
}

