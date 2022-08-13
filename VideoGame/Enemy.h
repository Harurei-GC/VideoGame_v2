#pragma once
#include "Actor.h"
class Enemy :public Actor
{
public:
	Enemy(class Game* game, Vector2 pos);
	~Enemy();
private:
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	class AIComponent* mAI;
};