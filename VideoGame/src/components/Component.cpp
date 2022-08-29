#include "Component.h"
#include "../actors/Actor.h"
Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
	,mScene(owner->GetScene())
{
	// Actor‚Ì¬•ªƒxƒNƒgƒ‹‚É’Ç‰Á
	mOwner->AddComponent(this);
}


Component::~Component()
{
	mOwner->RemoveComponent(this);
}


void Component::Update(float deltaTime)
{

}