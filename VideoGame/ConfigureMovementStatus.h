#pragma once
#include <map>
#include <vector>
#include "Math.h"
#include "Game.h"
#include "RigidbodyComponent.h"
#include "CircleComponent.h"
using RADIUS = float;


class ConfigureMovementStatus
{
public:
	ConfigureMovementStatus(Game* game);
	void Update(float deltaTime);
private:
	bool Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos);
	void JudgeActorsCollision(float deltaTime, Actor* you, Actor* me,char axis);
	void SwapSpeed(Vector2& aSpeed, Vector2& bSpeed);
	class Game* mGame;
	class Player* player;
	class Friend* fri;
	class Mob* mob;
	std::map<int, class Enemy*>enemy;
};