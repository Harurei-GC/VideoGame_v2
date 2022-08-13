#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "AIComponent.h"

Enemy::Enemy(Game* game, Vector2 pos)
	:Actor(game)
{
	SetRole(Role::Enemy);
	SetMass(10.0f);
	SetFriction(10.0f);
	SetPosition(pos);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(mGame->GetTexture("Assets/Enemy.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mMove = new MoveComponent(this);

	mAI = new AIComponent(this);

	mGame->AddEnemy(this);
}

Enemy::~Enemy()
{
	mGame->RemoveEnemy(this);
}