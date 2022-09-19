#include "RigidbodyComponent.h"
#include "../actors/Actor.h"
#include "CircleComponent.h"
#include "../scenes/Battle.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner, CircleComponent* circle)
	:Component(owner)
	, mSpeed(Vector2{ 0.0f,0.0f })
	, mAcceleration(Vector2{ 0.0f,0.0f })
	, mPowerSpeed(Vector2{ 0.0f,0.0f })
	, mForce(Vector2{ 0.0f,0.0f })
	, replacePos(Vector2{ 0.0f,0.0f })
	, isPowered(false)
	, battle(NULL)
{
}

void RigidbodyComponent::Start()
{
	battle = mOwner->GetScene()->GetGame()->battle;
}

void RigidbodyComponent::Update(float deltaTime)
{
	replacePos = mOwner->GetPosition();
	float mass = mOwner->GetMass();
	float friction = mOwner->GetFriction();
	Vector2 sign;
	(mForce.x < 0.0f) ? (sign.x = -1.0f) : (sign.x = 1.0f);
	if (mForce.x == 0.0f) { sign.x = 0.0f; }
	(mForce.y < 0.0f) ? (sign.y = -1.0f) : (sign.y = 1.0f);
	if (mForce.y == 0.0f) { sign.y = 0.0f; }
	// �����x�E���x�v�Z
	mAcceleration = Vector2(sign.x * mForce.x * mForce.x / mass, sign.y * mForce.y * mForce.y / mass);
	mSpeed += mAcceleration * deltaTime;

	// �X�s�[�h�A�b�v�{�^��������Ă��邩��ʒ[�ɂ��Ȃ���Ή���
	// �����ʂ͌��݂̑��x�{�萔
	if (isPowered && (replacePos.x > 20.0f && replacePos.x + 20.0f < WIDTH))
	{
		mSpeed.x += sign.x * mPowerSpeed.x;
	}
	if (isPowered && (replacePos.y > 20.0f && replacePos.y + 20.0f < HEIGHT))
	{
		mSpeed.y += sign.y * mPowerSpeed.y;
	}

	// �����x��0�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mAcceleration.x == 0) && (fabsf(mSpeed.x) > friction))
	{
		if (mSpeed.x > 0) { mSpeed.x -= friction; }
		else if (mSpeed.x < 0) { mSpeed.x += friction; }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mAcceleration.x == 0) && (fabsf(mSpeed.x) <= friction))
	{
		mSpeed.x = 0;
	}
	// �����x���O�̂Ƃ����X�s�[�h�����C�͈ȏ�ł���Ζ��C�͂��쓮
	if ((mAcceleration.y == 0) && (fabsf(mSpeed.y) > friction))
	{
		if (mSpeed.y > 0) { mSpeed.y -= friction; }
		else if (mSpeed.y < 0) { mSpeed.y += friction; }
	}
	// �X�s�[�h�����C�͂�菬������΃X�s�[�h��0�ɂ���
	else if ((mAcceleration.y == 0) && (fabsf(mSpeed.y) <= friction))
	{
		mSpeed.y = 0;
	}


	// ������x�ݒ�
	if (mOwner->GetRole() == Actor::Role::Player)
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

	// ���݂̈ʒu���X�V
	replacePos.x += mSpeed.x * deltaTime;
	replacePos.y += mSpeed.y * deltaTime;
	JudgeCollisionWithObject(deltaTime);
}

void RigidbodyComponent::JudgeCollisionWithObject(float deltaTime)
{
	std::vector<Vector2>objPos = battle->GetObjPosition();
	for (int i = 0; i < objPos.size(); i++)
	{
		if ((objPos.at(i).x - CHARACHIP_EDGE / 2 <= replacePos.x + mOwner->GetCircle()->GetRadius()) &&
			(replacePos.x - mOwner->GetCircle()->GetRadius() <= objPos.at(i).x + CHARACHIP_EDGE / 2))
		{
			if ((objPos.at(i).y - CHARACHIP_EDGE / 2 <= replacePos.y + mOwner->GetCircle()->GetRadius()) &&
				(replacePos.y - mOwner->GetCircle()->GetRadius() <= objPos.at(i).y + CHARACHIP_EDGE / 2))
			{
				replacePos -= mSpeed * deltaTime;
				// �ǂɓ��������Ƃ��ɂ����ɕǂ��痣�����悤�ɃX�s�[�h�Ɨ͂����Z�b�g
				mForce = Vector2{ 0.0f,0.0f };
				mSpeed = Vector2{ 0.0f,0.0f };
			}
		}
	}
}