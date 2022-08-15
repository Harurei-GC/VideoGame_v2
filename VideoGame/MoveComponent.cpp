#include "MoveComponent.h"
#include "Component.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Mob.h"
#include "CircleComponent.h"
#include "Player.h"
#include "InputComponent.h"
#include <iostream>
#include "Friend.h"
using namespace std;

// �����_�ł́APlayer��Mob�Ԃ̕��I�ȏ����ł������藧���Ȃ��B
// �����ύX���āAPlayer-Enemy�APlayer-Player�Ԃ̏Փ˂Ȃǂ���������B
// 
//

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mSpeed(Vector2{0.0f,0.0f})
	,mAcceleration(Vector2{0.0f,0.0f})
	,mForce(Vector2{0.0f,0.0f})
	,mPowerSpeed(Vector2(0.0f, 0.0f))
	,isPowered(false)
	,replacePos(Vector2{0.0f,0.0f})
	,player(NULL)
	,fri(NULL)
	,mob(NULL)
	,objPosition(NULL)
	,mePhy(Physics{0.0f,0.0f})
	,mRadius(0.0f)
{
	mRole = mOwner->GetRole();
}

void MoveComponent::Start()
{
}

void MoveComponent::Update(float deltaTime)
{
	player = mGame->GetPlayer();
	fri = mGame->GetFriend();
	mob = mGame->GetMob();
	objPosition = mGame->GetObjPosition();

	replacePos = mOwner->GetPosition();

	tPlayer.position = player->GetPosition();
	tPlayer.speed = player->GetInput()->GetSpeed();
	tPlayer.acceleration = player->GetInput()->GetAcceleration();
	tPlayer.force = player->GetInput()->GetForce();
	tPlayer.role = player->GetRole();
	tPlayer.powerSpeed = player->GetInput()->GetPowerSpeed();
	tPlayer.radius = player->GetCircle()->GetRadius();

	tFriend.position = fri->GetPosition();
	tFriend.speed = fri->GetMove()->GetSpeed();
	tFriend.acceleration = fri->GetMove()->GetAcceleration();
	tFriend.force = fri->GetMove()->GetForce();
	tFriend.role = fri->GetRole();
	tFriend.powerSpeed = fri->GetMove()->GetPowerSpeed();
	tFriend.radius = fri->GetCircle()->GetRadius();

	tMob.position = mob->GetPosition();
	tMob.speed = mob->GetMove()->GetSpeed();
	tMob.acceleration = mob->GetMove()->GetAcceleration();
	tMob.force = mob->GetMove()->GetForce();
	tMob.role = mob->GetRole();
	tMob.powerSpeed = mob->GetMove()->GetPowerSpeed();
	tMob.radius = mob->GetCircle()->GetRadius();

	// �Փ˔���
	// Player,Friend
	if (mRole == Actor::Role::Player)
	{
		mRadius = player->GetCircle()->GetRadius();
		if (!Intersect(*(player->GetCircle()), *(mob->GetCircle())))
		{
			SetTmpActorStatus(tMob);
			AccelMove(deltaTime, mob, player);
		}
		//if (!Intersect(*(player->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, player);
		//}
	}// Mob
	else if (mRole == Actor::Role::Mob)
	{
		mRadius = mob->GetCircle()->GetRadius();
		if (!Intersect(*(mob->GetCircle()), *(player->GetCircle())))
		{
			AccelMove(deltaTime, player, mob);
		}
		//if (!Intersect(*(mob->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, mob);
		//}
	}// Enemy
	else if (mRole == Actor::Role::Enemy)
	{
	}
	mOwner->SetPosition(replacePos);
}

void MoveComponent::SetTmpActorStatus(const TmpActorStatus& you)
{
	// WARNING: you���擾�ł��Ȃ������Ƃ��X�V����Ȃ�
	tyou.position = you.position;
	tyou.speed = you.speed;
	tyou.acceleration = you.acceleration;
	tyou.force = you.force;
	tyou.role = you.role;
	tyou.powerSpeed = you.powerSpeed;
	tyou.radius = you.radius;
}

void MoveComponent::AccelMove(float deltaTime, Actor* you, Actor* me)
{ 
	mePhy = { me->GetMass(), me->GetFriction() };

	meetMoveConditions(deltaTime,you,me);
	judgeCircleCollision(deltaTime, you, me, 'x');
	judgeCircleCollision(deltaTime, you, me, 'y');

	// ��ʒ[�ɓ�����Ɣ��˂��āA������̗͂𒴂����ꍇ�ɉ�ʊO�ɏo��
	if (0.0f > replacePos.x)
	{ 
		// ��ʊO�ɏo�Ă����Ƃ��Ă����x��SCREEN_OUT_FORCE��菬�����Ȃ�Β[�ɖ߂�
		if (mSpeed.x > -SCREEN_OUT_SPEED)
		{
			replacePos.x = 0.0f;
			mSpeed.x = -mSpeed.x;
		}
	}
	else if (replacePos.x > WIDTH) 
	{
		if (mSpeed.x < SCREEN_OUT_SPEED)
		{
			replacePos.x = WIDTH; 
			mSpeed.x = -mSpeed.x;
		}
	}

	if (0.0f > replacePos.y) 
	{ 
		if (mSpeed.y > -SCREEN_OUT_SPEED)
		{
			replacePos.y = 0.0f;
			mSpeed.y = -mSpeed.y;
		}
	}
	else if (replacePos.y > HEIGHT) 
	{
		if (mSpeed.y < SCREEN_OUT_SPEED)
		{
			replacePos.y = HEIGHT; 
			mSpeed.y = -mSpeed.y;
		}
	}

}

void MoveComponent::meetMoveConditions(float deltaTime, Actor* you, Actor* me)
{
	Vector2 sign;
	(mForce.x < 0.0f) ? (sign.x = -1.0f) : (sign.x = 1.0f);
	if (mForce.x == 0.0f) { sign.x = 0.0f; }
	(mForce.y < 0.0f) ? (sign.y = -1.0f) : (sign.y = 1.0f);
	if (mForce.y == 0.0f) { sign.y = 0.0f; }
	// �����x�E���x�v�Z
	mAcceleration = Vector2(sign.x * mForce.x * mForce.x / mePhy.mass, sign.y * mForce.y * mForce.y / mePhy.mass);
	mSpeed += mAcceleration * deltaTime;

	// �X�s�[�h�A�b�v�{�^��������Ă��邩��ʒ[�ɂ��Ȃ���Ή���
	// �����ʂ͌��݂̑��x�{�萔
	if (isPowered && (replacePos.x > 20.0f && replacePos.x + 20.0f < WIDTH))
	{
		mSpeed.x += sign.x * mPowerSpeed.x;
	}
	if (isPowered && (replacePos.y > 20.0f && replacePos.y + 20.0f < WIDTH))
	{
		mSpeed.y += sign.y * mPowerSpeed.y;
	}

	// �����x��0�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mAcceleration.x == 0) && (fabsf(mSpeed.x) > mePhy.friction))
	{
		if (mSpeed.x > 0) { mSpeed.x -= mePhy.friction; }
		else if (mSpeed.x < 0) { mSpeed.x += mePhy.friction; }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mAcceleration.x == 0) && (fabsf(mSpeed.x) <= mePhy.friction))
	{
		mSpeed.x = 0;
	}
	// �����x���O�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mAcceleration.y == 0) && (fabsf(mSpeed.y) > mePhy.friction))
	{
		if (mSpeed.y > 0) { mSpeed.y -= mePhy.friction; }
		else if (mSpeed.y < 0) { mSpeed.y += mePhy.friction; }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mAcceleration.y == 0) && (fabsf(mSpeed.y) <= mePhy.friction))
	{
		mSpeed.y = 0;
	}


	// ������x�ݒ�
	if (mRole == Actor::Role::Player)
	{
	if (mSpeed.x > 350.0f)
	{
		mSpeed.x = 350.0f;
		if (isPowered) { mSpeed.x += sign.x * mPowerSpeed.x; }
	}
	else if (mSpeed.x < -350.0f)
	{
		mSpeed.x = -350.0f;
		if (isPowered) { mSpeed.x += sign.x * mPowerSpeed.x; }
	}
	if (mSpeed.y > 300.0f)
	{
		mSpeed.y = 300.0f;
		if (isPowered) { mSpeed.y += sign.y * mPowerSpeed.y; }
	}
	else if (mSpeed.y < -300.0f)
	{
		mSpeed.y = -300.0f;
		if (isPowered) { mSpeed.y += sign.y * mPowerSpeed.y; }
	}

	}

	replacePos.x += mSpeed.x * deltaTime;
	replacePos.y += mSpeed.y * deltaTime;

	judgeBoxCollisionWithObject(deltaTime);
}

void MoveComponent::judgeBoxCollisionWithObject(float deltaTime)
{
	// WARNING:�Ǎۂ�player��friend���ڐG���Ă���ƁA
	//		player��Speed��Force�̃��Z�b�g��friend�Ƀy�[�X�g�����\������
	for (int i = 0; i < objPosition.size(); i++)
	{
		if ((objPosition.at(i).x - CHARACHIP_EDGE / 2 <= replacePos.x + mRadius) &&
			(replacePos.x - mRadius <= objPosition.at(i).x + CHARACHIP_EDGE / 2))
		{
			if ((objPosition.at(i).y - CHARACHIP_EDGE / 2 <= replacePos.y + mRadius) &&
				(replacePos.y - mRadius <= objPosition.at(i).y + CHARACHIP_EDGE / 2))
			{
				replacePos -= mSpeed * deltaTime;
				// �ǂɓ��������Ƃ��ɂ����ɕǂ��痣�����悤�ɃX�s�[�h�Ɨ͂����Z�b�g
				mForce = Vector2{ 0.0f,0.0f };
				mSpeed = Vector2{ 0.0f,0.0f };
			}
		}
	}
}

void MoveComponent::judgeCircleCollision(float deltaTime, Actor* you, Actor* me, char axis)
{
	float* position = NULL;
	float* speed = NULL;
	float* youSpeed = NULL;
	switch (axis)
	{
	case 'x':
		position = &replacePos.x;
		speed = &mSpeed.x;
		youSpeed = &tyou.speed.x;
		break;
	case 'y':
		position = &replacePos.y;
		speed = &mSpeed.y;
		youSpeed = &tyou.speed.y;
		break;
	default:
		return;
	}

	// �Փ˔���
	Vector2 diff = replacePos - tyou.position;
	float distSq = diff.LengthSq();
	float radiiSq = tyou.radius + mRadius;
	radiiSq *= radiiSq;
	if (distSq <= radiiSq)
	{
		*position -= *speed * deltaTime;
		// �Փ˂�������Ɏ����̃X�s�[�h��^����
		SwapSpeed(*speed, *youSpeed);
		switch (tyou.role)
		{
		case Actor::Role::Mob:
			mob->GetMove()->SetSpeed(tyou.speed);
			break;
		case Actor::Role::Player:
			player->GetInput()->SetSpeed(tyou.speed);
			break;
		case Actor::Role::Enemy:
			break;
		default:
			break;
		}
	}
}


template <typename T>
void MoveComponent::SwapSpeed(T& mobSpeed, T& playerSpeed)
{
	T tmp = mobSpeed;
	mobSpeed = playerSpeed;
	playerSpeed = tmp;
}


// �����x�ړ�ver �����Ă���������
void MoveComponent::NormalMove(Vector2& pos, Mob* mob, Player* player)
{
	pos.x += mSpeed.x;
	// AT:�������璷
	Vector2 diffX = pos - mob->GetPosition();
	float distSqX = diffX.LengthSq();
	float radiiSqX = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqX *= radiiSqX;
	if (distSqX <= radiiSqX)
	{
		pos.x -= mSpeed.x;
	}

	pos.y += mSpeed.y;
	// AT:�������璷
	Vector2 diffY = pos - mob->GetPosition();
	float distSqY = diffY.LengthSq();
	float radiiSqY = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqY *= radiiSqY;
	if (distSqY <= radiiSqY)
	{
		pos.y -= mSpeed.y;
	}

	if (0.0f > pos.x) { pos.x = 0.0f; }
	else if (pos.x > WIDTH) { pos.x = WIDTH; }

	if (0.0f > pos.y) { pos.y = 0.0f; }
	else if (pos.y > HEIGHT) { pos.y = HEIGHT; }
}
