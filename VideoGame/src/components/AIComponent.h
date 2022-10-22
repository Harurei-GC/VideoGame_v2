#pragma once
#include "components/Component.h"

namespace components
{
	class AIComponent :public Component
	{
	public:
		AIComponent(actors::Actor* owner, int updateOrder = 40);
	private:

	};
}
