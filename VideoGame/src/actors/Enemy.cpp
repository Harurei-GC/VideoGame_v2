#include "Enemy.h"
#include "../scenes/Scene.h"
#include "../components/SpriteComponent.h"
#include "../components/CircleComponent.h"
#include "../components/AIComponent.h"
#include "../components/RigidbodyComponent.h"

Enemy::Enemy(Scene* scene, Vector2 pos, int number)
	:Actor(scene)
	,mPosition(pos)
{
	SetID(number);
	SetRole(Role::Enemy);
	SetMass(10.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(mScene->GetTexture("assets/Enemy.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mRigidbody = new RigidbodyComponent(this, mCircle);

	mAI = new AIComponent(this);

	mScene->AddEnemy(GetID(), this);
}

Enemy::~Enemy()
{
	mScene->RemoveEnemy(GetID());
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