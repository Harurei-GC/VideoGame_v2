#pragma once
#include "Actor.h"

class Mob : public Actor
{
public:
	Mob(class Game* game);
	~Mob();
	class CircleComponent* GetCircle() { return mCircle; }
	class MoveComponent* GetMove() { return mMove; }
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;
private:
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
};