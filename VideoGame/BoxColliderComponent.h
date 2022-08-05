#pragma once
#include "Component.h"
#include "Actor.h"
#include "Math.h"

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(Actor* owner);

	

private:
	Vector2 mBox;
};