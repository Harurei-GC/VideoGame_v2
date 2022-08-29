#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	Player(class Scene* scene);
	~Player();
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	class CircleComponent* GetCircle() { return mCircle; }
	class RigidbodyComponent* GetRigidbody() { return mRigidbody; }
	class InputComponent* GetInput() { return mInput; }
private:
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	class InputComponent* mInput;
};