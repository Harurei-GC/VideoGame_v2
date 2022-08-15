#pragma once
#include "Actor.h"

class Friend :public Actor
{
public:
	Friend(class Game* game);
	class CircleComponent* GetCircle() { return mCircle; }
	class MoveComponent* GetMove() { return mMove; }
private:
	class SpriteComponent* sprite;
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	class AIComponent* mAI;
};