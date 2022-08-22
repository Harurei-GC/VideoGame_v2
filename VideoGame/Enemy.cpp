#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "AIComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game, Vector2 pos, int number)
	:Actor(game)
	,mPosition(pos)
{
	SetID(number);
	SetRole(Role::Enemy);
	SetMass(10.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(mGame->GetTexture("Assets/Enemy.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mRigidbody = new RigidbodyComponent(this, mCircle);

	//mMove = new MoveComponent(this);

	mAI = new AIComponent(this);

	mGame->AddEnemy(GetID(), this);
}

Enemy::~Enemy()
{
	mGame->RemoveEnemy(GetID());
}

void Enemy::UpdateActor(float deltaTime)
{
	//mStatus.position = GetPosition();
	//mStatus.speed = mMove->GetSpeed();
	//mStatus.acceleration = mMove->GetAcceleration();
	//mStatus.force = mMove->GetForce();
	//mStatus.role = GetRole();
	//mStatus.powerSpeed = mMove->GetPowerSpeed();
	//mStatus.radius = mCircle->GetRadius();

	// ここでdeleteが使われてメモリ解放される
	if (GetHP() <= 0) { SetState(State::Dead); }
}