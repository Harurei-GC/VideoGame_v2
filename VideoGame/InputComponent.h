#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;

	// 等速度移動
	//void SetSpeed(const uint8_t* keyState);
	// 等加速度移動
	void SetForce(const uint8_t* keyState);

	float GetMaxSpeed() const { return mMaxSpeed; }
	float GetMaxForce() const { return mMaxForce; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetRightKey() const { return mRightKey; }
	int GetLeftKey() const { return mLeftKey; }
	int GetPowerKey() const { return mPowerKey; }

	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetMaxForce(float force) { mMaxForce = force; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetRightKey(int key) { mRightKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
	void SetPowerKey(int key) { mPowerKey = key; }
	
private:
	float mMaxSpeed;
	float mMaxForce;
	// 垂直方向へ移動するためのキー
	int mForwardKey;
	int mBackKey;
	// 水平方向へ移動するためのキー
	int mRightKey;
	int mLeftKey;
	// Speedを増やすキー
	int mPowerKey;
};
