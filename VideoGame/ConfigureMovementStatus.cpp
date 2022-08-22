#include "ConfigureMovementStatus.h"
#include "Object.h"
#include "Actor.h"
#include "Player.h"
#include "Friend.h"
#include "Mob.h"
#include "Enemy.h"

// TODO:Enemyも実装
ConfigureMovementStatus::ConfigureMovementStatus(Game* game)
	:mGame(game)
{
	player = mGame->GetPlayer();
	fri = mGame->GetFriend();
	mob = mGame->GetMob();
}

void ConfigureMovementStatus::Update(float deltaTime)
{
	if (Intersect(player->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
		, player->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
	{
		//JudgeActorsCollision();// TODO:すべての条件分岐にこれ入れる
	}
	if (Intersect(player->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
		, player->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
	{

	}

	if (Intersect(fri->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
		, fri->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
	{

	}
	if (Intersect(fri->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
		, fri->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
	{

	}
	player->SetPosition(player->GetRigidbody()->GetReplacePosition());
	fri->SetPosition(fri->GetRigidbody()->GetReplacePosition());
	mob->SetPosition(mob->GetRigidbody()->GetReplacePosition());
}

bool ConfigureMovementStatus::Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos)
{
	Vector2 diff = apos - bpos;
	float distSq = diff.LengthSq();
	float radiiSq = arad + brad;
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}

void ConfigureMovementStatus::JudgeActorsCollision(float deltaTime,Actor* you, Actor* me, char axis)
{
	Vector2 position;
	Vector2 meSpeed;
	Vector2 youSpeed;
	position = me->GetRigidbody()->GetReplacePosition();
	meSpeed = me->GetRigidbody()->GetSpeed();
	youSpeed = you->GetRigidbody()->GetSpeed();
	
	//// 衝突判定
	// Update内で既に衝突判定しているのでは？
	//Vector2 diff = replacePos - tyou.position;
	//float distSq = diff.LengthSq();
	//float radiiSq = tyou.radius + mRadius;
	//radiiSq *= radiiSq;
	if (Intersect(me->GetCircle()->GetRadius(),you->GetCircle()->GetRadius(),me->GetRigidbody()->GetReplacePosition(),you->GetPosition()))
	{
		switch (axis)
		{
		case 'x':
			position.x -= meSpeed.x * deltaTime;
			break;
		case 'y':
			position.y -= meSpeed.y * deltaTime;
			break;
		default:
			break;
		}
		me->GetRigidbody()->SetReplacePosition(position);
		// 衝突した相手に自分のスピードを与える
		SwapSpeed(meSpeed, youSpeed);
		me->GetRigidbody()->SetSpeed(meSpeed);
		switch (you->GetRole())
		{
		case Actor::Role::Mob:
			mob->GetRigidbody()->SetSpeed(youSpeed);
			break;
		case Actor::Role::Player:
			player->GetRigidbody()->SetSpeed(youSpeed);
			break;
		case Actor::Role::Friend:
			fri->GetRigidbody()->SetSpeed(youSpeed);
			break;
		case Actor::Role::Enemy:
			//mGame->GetPersonalEnemy(tmpEnemyNum)->GetRigidbody()->SetSpeed(youSpeed);
			break;
		default:
			break;
		}
	}
}

void ConfigureMovementStatus::SwapSpeed(Vector2& aSpeed, Vector2& bSpeed)
{
	Vector2 tmp = aSpeed;
	aSpeed = bSpeed;
	bSpeed = tmp;
}