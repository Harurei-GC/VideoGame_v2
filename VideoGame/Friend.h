#pragma once
#include "Actor.h"

class Friend :public Actor
{
public:
	Friend(class Game* game);
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class SpriteComponent* sprite;
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	class AIComponent* mAI;
};