#include "Component.h"
#include "Actor.h"
Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
	,mGame(owner->GetGame())
{
	// Actor�̐����x�N�g���ɒǉ�
	mOwner->AddComponent(this);
}


Component::~Component()
{
	mOwner->RemoveComponent(this);
}


void Component::Update(float deltaTime)
{

}