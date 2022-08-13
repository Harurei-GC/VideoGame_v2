#include "Object.h"
#include "Game.h"
#include "Math.h"
#include "SpriteComponent.h"

Object::Object(Game* game, Vector2 pos)
	:Actor(game)
{
	SetRole(Role::Object);
	SetPosition(pos);
	SpriteComponent* sprite = new SpriteComponent(this,90);
	sprite->SetTexture(game->GetTexture("assets/Box.png"));

	mGame->AddObject(this);
}

Object::~Object()
{
	mGame->RemoveObject(this);
}

void Object::ActorInput(const uint8_t* keyState)
{

}

void Object::UpdateActor(float deltaTime)
{

}