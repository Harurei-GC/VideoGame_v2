#include "Enemy.h"
#include "../scenes/Scene.h"
#include "../components/SpriteComponent.h"
#include "../components/CircleComponent.h"
#include "../components/AIComponent.h"
#include "../components/RigidbodyComponent.h"
#include <iostream>

Enemy::Enemy(Scene* scene, Vector2 pos)
	:Actor(scene)
	,mInitialPosition(pos)
{
	SetRole(Role::Enemy);
	SetMass(10.0f);
	SetFriction(10.0f);
	SetPosition(mInitialPosition);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(mScene->GetTexture("assets/Enemy.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mRigidbody = new RigidbodyComponent(this, mCircle);

	mAI = new AIComponent(this);

}

Enemy::~Enemy()
{
	std::cout << "Enemy.cpp: Delete Enemy" << std::endl;
}

void Enemy::UpdateActor(float deltaTime)
{
	if (GetHP() <= 0) { SetState(State::Dead); }
}