#pragma once
#include "components/Component.h"
#include "actors/Actor.h"
#include "math/Math.h"

namespace components
{
	namespace collider
	{
		class BoxColliderComponent : public Component
		{
		public:
			BoxColliderComponent(actors::Actor* owner);
		private:
			Vector2 mBox;
		};
	}
}
