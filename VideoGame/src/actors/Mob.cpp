#include "Mob.h"
#include "../components/SpriteComponent.h"
#include "../Game.h"
#include "../components/CircleComponent.h"
#include "../components/RigidbodyComponent.h"

Mob::Mob(Game* game)
	:Actor(game)
{
	SetRole(Role::Mob);
	SetMass(10.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this,90);
	sprite->SetTexture(game->GetTexture("assets/Mob.png"));


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