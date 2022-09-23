#pragma once
#include "Scene.h"
#include "../managers/MakeDangeon.h"
#include <map>

#define ENEMIES 2

class Battle :public Scene
{
public:
	Battle(Game* game);
	~Battle();
	void Start()override;
	void ProcessInput()override;
	void UpdateGame()override;
	void GenerateOutput()override;
	void AddActor(Actor* actor)override;
	void RemoveActor(Actor* actor)override;
	void AddSprite(class SpriteComponent* sprite)override;
	void RemoveSprite(class SpriteComponent* sprite)override;
	void AddObject(class Object* object)override;
	void RemoveObject(class Object* object)override;
	std::vector<class Object*> GetObject() { return mObject; }
	std::vector<class Vector2> GetObjPosition()const { return objPosition; }
	std::map<int,class Enemy*> GetEnemiesMap() const { return mEnemy; }
	class Player* GetPlayer() { return mPlayer; }
	class Friend* GetFriend() { return mFriend; }
	class Mob* GetMob() { return mMob; }

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
	bool IsTimeOut(float deltaTime);
	std::vector<class Vector2> objPosition;
	class Player* mPlayer;
	class Friend* mFriend;
	class Mob* mMob;
	class Goal* mGoal;
	class Sprite* timerBackground;
	std::map<int, class Enemy*> mEnemy;
	std::vector<class Object*> mObject;
	MakeDangeon dangeon;
	class ConfigureMovementStatus* configMoveStatus;
	float timeLimit;
};



#include <vector>
#include "../Math.h"
#include "../scenes/Battle.h"
#include "../components/RigidbodyComponent.h"
#include "../components/CircleComponent.h"
using RADIUS = float;

class ConfigureMovementStatus
{
public:
	ConfigureMovementStatus(Battle* battle);
	void Start();
	void Update(float deltaTime);
	void SetActorsPosition();
	void EraseEnemy(int i) { enemy.erase(enemy.find(i)); }
private:
	bool Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos);
	void JudgeActorsCollision(float deltaTime, Actor* you, Actor* me,int ID, char axis);
	template<typename T>void SwapSpeed(T& aSpeed, T& bSpeed);
	bool IsMeDamaged(Vector2 youSpeed, Vector2 meSpeed, Vector2 youPos, Vector2 mePos);
	class Battle* cBattle;
	class Player* player;
	// NOTE:Enemyが完成するまでコメントアウト
	// class Friend* fri;
	class Mob* mob;
	std::map<int, class Enemy*>enemy;
};