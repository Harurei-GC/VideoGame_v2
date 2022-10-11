#include "components/collider/BoxColliderComponent.h"

namespace components
{
	namespace collider
	{
		BoxColliderComponent::BoxColliderComponent(actors::Actor* owner)
			:Component(owner)
		{
			mBox = owner->GetPosition();
		}


	}
}
