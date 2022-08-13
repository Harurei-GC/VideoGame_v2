#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent :public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 50);
	void Update(float deltaTime) override;

	// �����x�ړ��@�����Ă���������
	void NormalMove(Vector2& pos, class Mob* mob, class Player* player);
	// �������x�ňړ�(Update()���Ŏg�p)
	void AccelMove(float deltaTime, Vector2& pos, class Actor* you, class Actor* me);
	void SwapSpeed(float& mobSpeed, float& playerSpeed);
	
	float GetVerticalSpeed() const { return mVerticalSpeed; }
	float GetHorizontalSpeed() const { return mHorizontalSpeed; }
	Vector2 GetPowerSpeed() const { return mPowerSpeed; }
	float GetVerticalForce() const { return mVerticalForce; }
	float GetHorizontalForce() const { return mHorizontalForce; }
	void SetVerticalSpeed(float speed) { mVerticalSpeed = speed; }
	void SetHorizontalSpeed(float speed) { mHorizontalSpeed = speed; }
	void SetPowerSpeed(Vector2 speed){ mPowerSpeed = speed; }
	void SetVerticalForce(float force) { mVerticalForce = force; }
	void SetHorizontalForce(float force) { mHorizontalForce = force; }

protected:
	// �X�s�[�h�A�b�v�{�^���������ꂽ���ǂ���
	bool isPoweredX;
	bool isPoweredY;

private:
	// AT:float�^�ł͂Ȃ�Vector2�^�Ő��������܂Ƃ߂���̂ł́H
	// ���������X�s�[�h
	float mHorizontalSpeed;
	// �������������x
	float mHorizontalAcceleration;
	// ���������ɉ�����
	float mHorizontalForce;
	// ���������X�s�[�h
	float mVerticalSpeed;
	// �������������x
	float mVerticalAcceleration;
	// ���������ɉ�����
	float mVerticalForce;
	// �X�s�[�h�A�b�v�{�^���������Ƃ��̒ǉ����x
	Vector2 mPowerSpeed;
};