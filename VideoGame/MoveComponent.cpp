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

// �����_�ł́APlayer��Mob�Ԃ̕��I�ȏ����ł������藧���Ȃ��B
// �����ύX���āAPlayer-Enemy�APlayer-Player�Ԃ̏Փ˂Ȃǂ���������B
// 
//

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mHorizontalSpeed(0.0f)
	,mHorizontalAcceleration(0.0f)
	,mHorizontalForce(0.0f)
	,mVerticalSpeed(0.0f)
	,mVerticalAcceleration(0.0f)
	,mVerticalForce(0.0f)
	,mPowerSpeed(Vector2(0.0f, 0.0f))
	,isPoweredX(false)
	,isPoweredY(false)
{
}

void MoveComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();

	Player* player = mGame->GetPlayer();
	Friend* fri = mGame->GetFriend();
	Mob* mob = mGame->GetMob();

	// �Փ˔���
	// Player,Friend
	if (mOwner->GetRole() == Actor::Role::Player)
	{
		if (!Intersect(*(player->GetCircle()), *(mob->GetCircle())))
		{
			AccelMove(deltaTime, pos, mob, player);
		}
		//if (!Intersect(*(player->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, player);
		//}
	}// Mob
	else if (mOwner->GetRole() == Actor::Role::Mob)
	{
		if (!Intersect(*(mob->GetCircle()), *(player->GetCircle())))
		{
			AccelMove(deltaTime, pos, player, mob);
		}
		//if (!Intersect(*(mob->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, mob);
		//}
	}// Enemy
	else if (mOwner->GetRole() == Actor::Role::Enemy)
	{

	}

	mOwner->SetPosition(pos);
}

// ��{�I�Ȉړ��i�������x�I�j
// �����w�ɂ̂��Ƃ�A�́E�����x�E���x��3�v�f�Ōv�Z
// ���C�͂��l�����A����ɏ�����x���ݒ肵�Ă���B
//
void MoveComponent::AccelMove(float deltaTime, Vector2& pos, Actor* you, Actor* me)
{ 

	Mob* mob = mGame->GetMob();
	Player* player = mGame->GetPlayer();
	const std::vector<class Vector2>objPosition = mGame->GetObjPosition();


	float negX;
	if(mHorizontalForce <0.0f){ negX = -1.0f; }
	else { negX = 1.0f; }
	// �����x�E���x�v�Z
	mHorizontalAcceleration = negX * mHorizontalForce * mHorizontalForce / me->GetMass();
	mHorizontalSpeed += mHorizontalAcceleration * deltaTime;
	// �X�s�[�h�A�b�v�{�^��������Ă��邩��ʒ[�ɂ��Ȃ���Ή���
	if (isPoweredX && pos.x > 20.0f && pos.x + 20.0f< WIDTH) 
	{ mHorizontalSpeed += negX * mPowerSpeed.x; }
	// �����x��0�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mHorizontalAcceleration == 0 )&& (fabsf(mHorizontalSpeed) > me->GetFriction()))
	{ 
		if(mHorizontalSpeed > 0){mHorizontalSpeed -= me->GetFriction(); }
		else if (mHorizontalSpeed < 0) { mHorizontalSpeed += me->GetFriction(); }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mHorizontalAcceleration == 0) && (fabsf(mHorizontalSpeed) <= me->GetFriction()))
	{
		mHorizontalSpeed = 0;
	}
	// ������x�ݒ�(�v���C���[�̂�)
	if (me->GetRole() == Actor::Role::Player)
	{
		if (mHorizontalSpeed > 350.0f)
		{
			mHorizontalSpeed = 350.0f;
			if (isPoweredX) { mHorizontalSpeed += negX * mPowerSpeed.x; }
		}
		else if (mHorizontalSpeed < -350.0f)
		{
			mHorizontalSpeed = -350.0f;
			if (isPoweredX) { mHorizontalSpeed += negX * mPowerSpeed.x; }
		}
	}
	pos.x += mHorizontalSpeed * deltaTime;
	// �Փ˔���@HACK:�������璷
	Vector2 diffX = pos - you->GetPosition();
	float distSqX = diffX.LengthSq();
	float radiiSqX = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqX *= radiiSqX;
	if (distSqX <= radiiSqX)
	{
		pos.x -= mHorizontalSpeed * deltaTime;
		// �Փ˂�������Ɏ����̃X�s�[�h��^����
		if (me->GetRole() == Actor::Role::Mob)
		{
			float playerSpeed = player->GetInput()->GetHorizontalSpeed();
			SwapSpeed(mHorizontalSpeed, playerSpeed);
			player->GetInput()->SetHorizontalSpeed(playerSpeed);
		}
		else if (me->GetRole() == Actor::Role::Player)
		{
			float mobSpeed = mob->GetMove()->GetHorizontalSpeed();
			SwapSpeed(mHorizontalSpeed, mobSpeed);
			mob->GetMove()->SetHorizontalSpeed(mobSpeed);
		}
	}



	float negY;
	if (mVerticalForce < 0.0f) { negY = -1.0f; }
	else { negY = 1.0f; }
	// �����x�E���x�v�Z
	mVerticalAcceleration = negY * mVerticalForce * mVerticalForce / me->GetMass();
	mVerticalSpeed += mVerticalAcceleration * deltaTime;
	// �X�s�[�h�A�b�v�{�^����������Ă��邩��ʒ[�ɂ��Ȃ���Ή���
	if (isPoweredY && pos.y > 20.0f && pos.y + 20.0f < WIDTH)
	{ mVerticalSpeed += negY * mPowerSpeed.y; }
	// �����x���O�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mVerticalAcceleration == 0) && (fabsf(mVerticalSpeed) > me->GetFriction()))
	{
		if (mVerticalSpeed > 0) { mVerticalSpeed -= me->GetFriction(); }
		else if (mVerticalSpeed < 0) { mVerticalSpeed += me->GetFriction(); }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mVerticalAcceleration == 0) && (fabsf(mVerticalSpeed) <= me->GetFriction()))
	{
		mVerticalSpeed = 0;
	}
	// ������x�ݒ�
	if (mVerticalSpeed > 300.0f)
	{ 
		mVerticalSpeed = 300.0f; 
		if(isPoweredY){ mVerticalSpeed += negY * mPowerSpeed.y; }
	}
	else if (mVerticalSpeed < -300.0f) {
		mVerticalSpeed = -300.0f; 
		if (isPoweredY) { mVerticalSpeed += negY * mPowerSpeed.y; }
	}
	pos.y += mVerticalSpeed * deltaTime;
	// �Փ˔���@HACK:�������璷
	Vector2 diffY = pos - you->GetPosition();
	float distSqY = diffY.LengthSq();
	float radiiSqY = mGame->GetMob()->GetCircle()->GetRadius() + mGame->GetPlayer()->GetCircle()->GetRadius();
	radiiSqY *= radiiSqY;
	if (distSqY <= radiiSqY)
	{
		pos.y -= mVerticalSpeed * deltaTime;
		//�Փ˂�������Ɏ����̃X�s�[�h��^����

		if (me->GetRole() == Actor::Role::Mob)
		{
			float playerSpeed = player->GetInput()->GetVerticalSpeed();
			SwapSpeed(mVerticalSpeed, playerSpeed);
			player->GetInput()->SetVerticalSpeed(playerSpeed);
		}
		else if (me->GetRole() == Actor::Role::Player)
		{
			float mobSpeed = mob->GetMove()->GetVerticalSpeed();
			SwapSpeed(mVerticalSpeed, mobSpeed);
			mob->GetMove()->SetVerticalSpeed(mobSpeed);
		}
	}

	float meRadious = 0.0f;
	if (me->GetRole() == Actor::Role::Mob)
	{
		meRadious = mGame->GetMob()->GetCircle()->GetRadius();
	}
	else if (me->GetRole() == Actor::Role::Player)
	{
		meRadious = mGame->GetPlayer()->GetCircle()->GetRadius();
	}
	// �S�Ă�Object�N���X�ɑ΂��āAActor���d�Ȃ��Ă��Ȃ�������
	for (int i = 0; i < objPosition.size(); i++)
	{
		if ((objPosition.at(i).x - CHARACHIP_EDGE/2 <= pos.x + meRadious) &&
			(pos.x - meRadious<= objPosition.at(i).x + CHARACHIP_EDGE /2))
		{
			if ((objPosition.at(i).y - CHARACHIP_EDGE/2<= pos.y + meRadious) &&
			(pos.y - meRadious<= objPosition.at(i).y + CHARACHIP_EDGE / 2))
			{
				pos.y -= mVerticalSpeed * deltaTime;
				pos.x -= mHorizontalSpeed * deltaTime;
				// �ǂɓ��������Ƃ��ɂ����ɕǂ��痣�����悤�ɃX�s�[�h�Ɨ͂����Z�b�g
				mHorizontalForce = 0.0f;
				mHorizontalSpeed = 0.0f;
				mVerticalForce = 0.0f;
				mVerticalSpeed = 0.0f;
			}
		}

	
	}


	// �ǂɓ�����Ɣ��˂��āA������̗͂𒴂����ꍇ�ɉ�ʊO�ɏo��
	// ���[�ɂ��������Ƃ�
	if (0.0f > pos.x)
	{ 
		std::cout << "Mob Out:" << mGame->GetMob()->GetMove()->GetHorizontalSpeed() << std::endl;
		// ��ʊO�ɏo�Ă����Ƃ��Ă����x��SCREEN_OUT_FORCE��菬�����Ȃ�Β[�ɖ߂�
		if (mHorizontalSpeed > -SCREEN_OUT_SPEED)
		{
			pos.x = 0.0f;
			mHorizontalSpeed = -mHorizontalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}
	// �E�[�ɂ��������Ƃ�
	else if (pos.x > WIDTH) 
	{
		if (mHorizontalSpeed < SCREEN_OUT_SPEED)
		{
			pos.x = WIDTH; 
			mHorizontalSpeed = -mHorizontalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}

	if (0.0f > pos.y) 
	{ 
		if (mVerticalSpeed > -SCREEN_OUT_SPEED)
		{
			pos.y = 0.0f;
			mVerticalSpeed = -mVerticalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}
	else if (pos.y > HEIGHT) 
	{
		if (mVerticalSpeed < SCREEN_OUT_SPEED)
		{
			pos.y = HEIGHT; 
			mVerticalSpeed = -mVerticalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}

}

void MoveComponent::SwapSpeed(float& mobSpeed, float& playerSpeed)
{
	float tmp = mobSpeed;
	mobSpeed = playerSpeed;
	playerSpeed = tmp;
}


// �����x�ړ�ver �����Ă���������
void MoveComponent::NormalMove(Vector2& pos, Mob* mob, Player* player)
{
	pos.x += mHorizontalSpeed;
	// AT:�������璷
	Vector2 diffX = pos - mob->GetPosition();
	float distSqX = diffX.LengthSq();
	float radiiSqX = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqX *= radiiSqX;
	if (distSqX <= radiiSqX)
	{
		pos.x -= mHorizontalSpeed;
	}

	pos.y += mVerticalSpeed;
	// AT:�������璷
	Vector2 diffY = pos - mob->GetPosition();
	float distSqY = diffY.LengthSq();
	float radiiSqY = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqY *= radiiSqY;
	if (distSqY <= radiiSqY)
	{
		pos.y -= mVerticalSpeed;
	}

	if (0.0f > pos.x) { pos.x = 0.0f; }
	else if (pos.x > WIDTH) { pos.x = WIDTH; }

	if (0.0f > pos.y) { pos.y = 0.0f; }
	else if (pos.y > HEIGHT) { pos.y = HEIGHT; }
}
