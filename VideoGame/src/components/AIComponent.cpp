#include "AIComponent.h"
#include "../actors/Actor.h"
#include "Component.h"

AIComponent::AIComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{

}