#include "Mob.h"
#include "../components/SpriteComponent.h"
#include "../scenes/Scene.h"
#include "../components/CircleComponent.h"
#include "../components/RigidbodyComponent.h"

Mob::Mob(Scene* scene)
	:Actor(scene)
{
	SetRole(Role::Mob);
	SetMass(10.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this,90);
	sprite->SetTexture(scene->GetTexture("assets/Mob.png"));


	mCircle = new CircleComponent(this);
	mCircle->SetRadius(8.5f);

	mRigidbody = new RigidbodyComponent(this, mCircle);

	//mMove = new MoveComponent(this);
}

Mob::~Mob()
{
}

void Mob::UpdateActor(float deltaTime)
{

}

void Mob::ActorInput(const uint8_t* keyState)
{

}