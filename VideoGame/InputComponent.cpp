#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mRightKey(0)
	, mLeftKey(0)
	, mPowerKey(0)
	, mMaxSpeed(0.0f)
	, mMaxForce(0.0f)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	isPowered = false;
	inputForce = Vector2{ 0.0f,0.0f };
	if (keyState[mRightKey])
	{
		enableForce(inputForce.x, false);
	}
	if (keyState[mLeftKey])
	{
		enableForce(inputForce.x, true);
	}
	if (keyState[mForwardKey])
	{
		enableForce(inputForce.y, true);
	}
	if (keyState[mBackKey])
	{
		enableForce(inputForce.y, false);
	}
	if (keyState[mPowerKey])
	{
		isPowered = true;
	}
	SetForce(inputForce);
}

void InputComponent::enableForce(float& force ,bool isNegative)
{
	if (isNegative) { force -= mMaxForce; }
	else{ force += mMaxForce; }
}

