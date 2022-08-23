#pragma once
#include <cstdint>
#include "Component.h"
#include "../Math.h"

class InputComponent : public Component
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForce() const { return mMaxForce; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetRightKey() const { return mRightKey; }
	int GetLeftKey() const { return mLeftKey; }
	int GetPowerKey() const { return mPowerKey; }

	void SetMaxForce(float force) { mMaxForce = force; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetRightKey(int key) { mRightKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
	void SetPowerKey(int key) { mPowerKey = key; }
	
private:
	void enableForce(float& force, bool isNegative);

	class RigidbodyComponent* rigidbody;
	float mMaxForce;
	int mForwardKey;
	int mBackKey;
	int mRightKey;
	int mLeftKey;
	int mPowerKey;
	Vector2 inputForce;
};
