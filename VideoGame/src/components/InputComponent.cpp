#include "components/InputComponent.h"
#include "actors/Actor.h"
#include "components/RigidbodyComponent.h"
#include <iostream>

namespace components
{
	InputComponent::InputComponent(actors::Actor* owner)
		:Component(owner)
		, mUpKey(0)
		, mDownKey(0)
		, mRightKey(0)
		, mLeftKey(0)
		, mPowerKey(0)
		, mMaxForce(0.0f)
	{
		rigidbody = mOwner->GetRigidbody();
	}

	void InputComponent::ProcessInput(const uint8_t* keyState)
	{
		rigidbody->SetIsPowered(false);
		inputForce = Vector2{ 0.0f,0.0f };
		if (keyState[mRightKey])
		{
			enableForce(inputForce.x, false);
		}
		if (keyState[mLeftKey])
		{
			enableForce(inputForce.x, true);
		}
		if (keyState[mUpKey])
		{
			enableForce(inputForce.y, true);
		}
		if (keyState[mDownKey])
		{
			enableForce(inputForce.y, false);
		}
		if (keyState[mPowerKey])
		{
			rigidbody->SetIsPowered(true);
		}
		rigidbody->SetForce(inputForce);
	}

	void InputComponent::enableForce(float& force ,bool isNegative)
	{
		if (isNegative) { force -= mMaxForce; }
		else{ force += mMaxForce; }
	}


}
