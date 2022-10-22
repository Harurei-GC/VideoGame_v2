#pragma once
#include "components/Component.h"
#include "math/Math.h"

namespace components
{
	namespace collider
	{
		class CircleComponent :public Component
		{
		public:
			CircleComponent(actors::Actor* owner);
			void SetRadius(float radius) { mRadius = radius; }
			float GetRadius()const;
			const Vector2& GetCenter() const;
		private:
			float mRadius;
		};
	}
}
