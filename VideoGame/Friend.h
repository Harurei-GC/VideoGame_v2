#pragma once
#include "Actor.h"

class Friend :public Actor
{
public:
	Friend(class Game* game);
	~Friend();
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	class CircleComponent* GetCircle() { return mCircle; }
	class MoveComponent* GetMove() { return mMove; }
private:
	class SpriteComponent* sprite;
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	class AIComponent* mAI;
};