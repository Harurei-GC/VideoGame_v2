#include "BoxColliderComponent.h"
#include "Game.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
	:Component(owner)
{
	mBox = owner->GetPosition();
}

