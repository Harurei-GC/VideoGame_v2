#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
	:Component(owner)
{
	mBox = owner->GetPosition();
}

