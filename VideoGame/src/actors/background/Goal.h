#pragma once
#include "actors/Actor.h"
#include "managers/MakeDangeon.h"

namespace actors
{
	namespace characters
	{
		class MBox;
	}
	namespace background
	{
		class Goal;
	}
}
namespace scenes { class Scene; }
namespace managers { class MakeDangeon; }
namespace math { class Random; }

namespace actors
{
	namespace background
	{
		class Goal : public Actor
		{
		public:
			Goal(scenes::Scene* scene);

			void UpdateActor(float deltaTime) override;
			void ActorInput(const uint8_t* keyState) override;

			Vector2Int RandomPosition(managers::MakeDangeon* dangeon);
	
		private:
			math::Random* rand;
		};

		// 衝突していればtrue
		bool GoalIntersect(const actors::background::Goal& goal, actors::characters::MBox& box);
	}
}
