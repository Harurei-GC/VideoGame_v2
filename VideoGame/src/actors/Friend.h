#pragma once
#include "Actor.h"

class Friend :public Actor
{
public:
	Friend(class Game* game);
	~Friend();
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	class CircleComponent* GetCircle() override { return mCircle; }
	class RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
	//class MoveComponent* GetMove() { return mMove; }
private:
	class SpriteComponent* sprite;
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	//class MoveComponent* mMove;
	class AIComponent* mAI;
};