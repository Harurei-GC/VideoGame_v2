#include "components/AIComponent.h"
#include "actors/Actor.h"
#include "components/Component.h"

namespace components
{
	AIComponent::AIComponent(actors::Actor* owner, int updateOrder)
		:Component(owner, updateOrder)
	{

	}
}
