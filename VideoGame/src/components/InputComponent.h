#pragma once
#include <cstdint>
#include "components/Component.h"
#include "math/Math.h"

namespace components
{
	class RigidbodyComponent;

	class InputComponent : public Component
	{
	public:
		InputComponent(actors::Actor* owner);
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

		RigidbodyComponent* rigidbody;
		float mMaxForce;
		int mForwardKey;
		int mBackKey;
		int mRightKey;
		int mLeftKey;
		int mPowerKey;
		Vector2 inputForce;
	};

}
