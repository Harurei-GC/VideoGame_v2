// @todo –¼‘O‚ðBlock‚ÉƒŠƒl[ƒ€‚µ‚½‚¢

#include "Object.h"
#include "../scenes/Scene.h"
#include "Math.h"
#include "../components/SpriteComponent.h"

Object::Object(Scene* scene, Vector2 pos)
	:Actor(scene)
{
	SetRole(Role::Object);
	SetPosition(pos);
	SpriteComponent* sprite = new SpriteComponent(this,90);
	sprite->SetTexture(scene->GetTexture("assets/Tree.png"));

	mScene->AddObject(this);
}

Object::~Object()
{
	mScene->RemoveObject(this);
}

void Object::ActorInput(const uint8_t* keyState)
{

}

void Object::UpdateActor(float deltaTime)
{

}