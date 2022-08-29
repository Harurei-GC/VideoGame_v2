#pragma once
#include <map>
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
	void Update(float deltaTime);
	void SetActorsPosition();
private:
	bool Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos);
	void JudgeActorsCollision(float deltaTime, Actor* you, Actor* me,char axis);
	template<typename T>void SwapSpeed(T& aSpeed, T& bSpeed);
	class Battle* mScene;
	class Player* player;
	class Friend* fri;
	class Mob* mob;
	std::map<int, class Enemy*>enemy;
};