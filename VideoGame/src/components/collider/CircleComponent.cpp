#include "CircleComponent.h"
#include "actors/Actor.h"

namespace components
{
	namespace collider
	{
		CircleComponent::CircleComponent(actors::Actor* owner)
			:Component(owner)
			,mRadius(0.0f)
		{

		}

		float CircleComponent::GetRadius() const
		{
			return mOwner->GetScale() * mRadius;
		}

		const Vector2& CircleComponent::GetCenter() const
		{
			return mOwner->GetPosition();
		}

	}
}
