#pragma once
#include "actors/Actor.h"


namespace scenes { class Scene; }

namespace actors
{
	namespace characters
	{
		class CharacterActor : public Actor
		{
		public:
			CharacterActor(scenes::Scene* scene);
			~CharacterActor();
		};
	}
}
