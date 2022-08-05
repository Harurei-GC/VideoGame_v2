#pragma once
#include "Actor.h"
#include "Mob.h"
#include "MakeDangeon.h"

class Goal : public Actor
{
public:
	Goal(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	Vector2Int RandomPosition(class MakeDangeon* dangeon);
	
private:
	class Random* rand;
};

// 衝突していればtrue
bool GoalIntersect(const Goal& goal, Mob& mob);