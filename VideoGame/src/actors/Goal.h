#pragma once
#include "Actor.h"
#include "Mob.h"
#include "../managers/MakeDangeon.h"

class Goal : public Actor
{
public:
	Goal(class Scene* scene);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	Vector2Int RandomPosition(class MakeDangeon* dangeon);
	
private:
	class Random* rand;
};

// �Փ˂��Ă����true
bool GoalIntersect(const Goal& goal, Mob& mob);