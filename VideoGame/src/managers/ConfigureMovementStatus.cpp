#include "ConfigureMovementStatus.h"
#include "../actors/Object.h"
#include "../actors/Actor.h"
#include "../actors/Player.h"
#include "../actors/Friend.h"
#include "../actors/Mob.h"
#include "../actors/Enemy.h"

// TODO:Enemy‚àŽÀ‘•
ConfigureMovementStatus::ConfigureMovementStatus(Battle* battle)
	:cBattle(battle)
{

}

void ConfigureMovementStatus::Start()
{
	player = cBattle->GetPlayer();
	fri = cBattle->GetFriend();
	mob = cBattle->GetMob();
}

void ConfigureMovementStatus::Update(float deltaTime)
{
	// NOTE:xŽ²‘¤‚ÆyŽ²‘¤—¼•û‰ñ‚·
	for (int i = 0; i < 2; i++)
	{
		char a;
		(i == 0) ? a = 'x' : a = 'y';
		if (Intersect(player->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
			, player->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, fri, player, a);
		}
		if (Intersect(player->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
			, player->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, mob, player, a);
		}

		if (Intersect(fri->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
			, fri->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, player, fri, a);
		}
		if (Intersect(fri->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
			, fri->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, mob, fri, a);
		}

		if (Intersect(mob->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
			, mob->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, player, mob, a);
		}
		if (Intersect(mob->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
			, mob->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, fri, mob, a);
		}
	}
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
	
	//// Õ“Ë”»’è
	// Update“à‚ÅŠù‚ÉÕ“Ë”»’è‚µ‚Ä‚¢‚é‚Ì‚Å‚ÍH
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
			SwapSpeed(meSpeed.x, youSpeed.x);
			break;
		case 'y':
			position.y -= meSpeed.y * deltaTime;
			SwapSpeed(meSpeed.y, youSpeed.y);
			break;
		default:
			break;
		}
		me->GetRigidbody()->SetReplacePosition(position);
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

template<typename T>
void ConfigureMovementStatus::SwapSpeed(T& aSpeed, T& bSpeed)
{
	T tmp = aSpeed;
	aSpeed = bSpeed;
	bSpeed = tmp;
}

void ConfigureMovementStatus::SetActorsPosition()
{
	player->SetPosition(player->GetRigidbody()->GetReplacePosition());
	fri->SetPosition(fri->GetRigidbody()->GetReplacePosition());
	mob->SetPosition(mob->GetRigidbody()->GetReplacePosition());
}