#pragma once
#include "actors/Actor.h"


namespace scenes { class Scene; }
namespace components { 
	class SpriteComponent;
	class AIComponent;
}

namespace actors
{
	namespace characters
	{
		class Friend :public Actor
		{
		public:
			Friend(scenes::Scene* scene);
			~Friend();
			void UpdateActor(float deltaTime) override;
			void ActorInput(const uint8_t* keyState) override;
			col::CircleComponent* GetCircle() override { return mCircle; }
			components::RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
		private:
			components::SpriteComponent* sprite;
			col::CircleComponent* mCircle;
			components::RigidbodyComponent* mRigidbody;
			components::AIComponent* mAI;
		};
	}
}
