#pragma once
#include "Actor.h"

class Mob : public Actor
{
public:
	Mob(class Scene* scene);
	~Mob();
	class CircleComponent* GetCircle() override { return mCircle; }
	class RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
	//class MoveComponent* GetMove() { return mMove; }
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;
private:
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	//class MoveComponent* mMove;
};