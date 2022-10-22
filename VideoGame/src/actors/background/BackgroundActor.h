#pragma once
#include "actors/Actor.h"

namespace scenes { class Scene; }

namespace actors
{
	namespace background
	{
		class BackgroundActor : public Actor
		{
		public:
			BackgroundActor(scenes::Scene* scene);
			~BackgroundActor();
		};
	}
}
