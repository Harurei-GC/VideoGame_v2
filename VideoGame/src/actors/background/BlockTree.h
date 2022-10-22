#pragma once
#include "actors/Actor.h"

namespace scenes { class Scene; }

namespace actors
{
	namespace background
	{
		class BlockTree : public Actor
		{
		public:
			BlockTree(scenes::Scene* scene, Vector2 pos);
			~BlockTree();

			void ActorInput(const uint8_t* keyState) override;
			void UpdateActor(float deltaTme) override;
		private:

		};
	}
}
