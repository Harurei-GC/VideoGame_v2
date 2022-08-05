#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mRightKey(0)
	, mLeftKey(0)
	, mMaxSpeed(0.0f)
	, mMaxForce(0.0f)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	SetForce(keyState); // SetSpeedÇ©SetForceÇÃÇ«ÇøÇÁÇ©çÃóp
}

void InputComponent::SetForce(const uint8_t* keyState)
{
	isPoweredX = false;
	isPoweredY = false;
	float verticalForce = 0.0f;
	if (keyState[mForwardKey])
	{
		verticalForce -= mMaxForce;
		if (keyState[mPowerKey])// âüÇµÇ¡ÇœÇ»ÇµÇ≈ÇÕÇ»Ç≠òAë≈Ç∑ÇÈÇÊÇ§Ç…ÇµÇΩÇ¢
		{
			isPoweredY = true;
		}
	}
	if (keyState[mBackKey])
	{
		verticalForce += mMaxForce;
		if (keyState[mPowerKey])// âüÇµÇ¡ÇœÇ»ÇµÇ≈ÇÕÇ»Ç≠òAë≈Ç∑ÇÈÇÊÇ§Ç…ÇµÇΩÇ¢
		{
			isPoweredY = true;
		}
	}
	SetVerticalForce(verticalForce);

	float horizontalForce = 0.0f;
	if (keyState[mRightKey])
	{
		horizontalForce += mMaxForce;
		if (keyState[mPowerKey])
		{
			isPoweredX = true;
		}
	}
	if (keyState[mLeftKey])
	{
		horizontalForce -= mMaxForce;
		if (keyState[mPowerKey])
		{
			isPoweredX = true;
		}
	}
	SetHorizontalForce(horizontalForce);
}

