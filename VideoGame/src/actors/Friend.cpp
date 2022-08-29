#include "Friend.h"
#include "../scenes/Scene.h"
#include "../components/SpriteComponent.h"
#include "../components/CircleComponent.h"
#include "../components/AIComponent.h"
#include "../components/RigidbodyComponent.h"

Friend::Friend(Scene* scene)
	:Actor(scene)
{

	SetRole(Role::Friend);
	SetMass(5.0f);
	SetFriction(10.0f);

	sprite = new SpriteComponent(this);
	sprite->SetTexture(scene->GetTexture("assets/Friend.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mRigidbody = new RigidbodyComponent(this, mCircle);

	//mMove = new MoveComponent(this);

	mAI = new AIComponent(this);
}

Friend::~Friend()
{
	
}

void Friend::UpdateActor(float deltaTime)
{

}

void Friend::ActorInput(const uint8_t* keyState)
{

}