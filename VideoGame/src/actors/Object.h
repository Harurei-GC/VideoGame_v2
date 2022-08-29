#pragma once
#include "Actor.h"

class Object : public Actor
{
public:
	Object(class Scene* scene, Vector2 pos);
	~Object();

	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTme) override;
private:

};