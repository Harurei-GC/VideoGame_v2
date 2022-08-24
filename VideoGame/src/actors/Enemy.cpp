#include "Enemy.h"
#include "../Game.h"
#include "../components/SpriteComponent.h"
#include "../components/CircleComponent.h"
#include "../components/AIComponent.h"
#include "../components/RigidbodyComponent.h"

Enemy::Enemy(Game* game, Vector2 pos, int number)
	:Actor(game)
	,mPosition(pos)
{
	SetID(number);
	SetRole(Role::Enemy);
	SetMass(10.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(mGame->GetTexture("assets/Enemy.png"));

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

	// ‚±‚±‚Ådelete‚ªg‚í‚ê‚Äƒƒ‚ƒŠ‰ğ•ú‚³‚ê‚é
	if (GetHP() <= 0) { SetState(State::Dead); }
}