#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;

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
	void enableForce(float& force, bool isNegative);

	float mMaxSpeed;
	float mMaxForce;
	int mForwardKey;
	int mBackKey;
	int mRightKey;
	int mLeftKey;
	int mPowerKey;
	Vector2 inputForce;
};
