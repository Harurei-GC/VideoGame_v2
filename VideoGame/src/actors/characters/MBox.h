#pragma once
#include "actors/Actor.h"


namespace scenes { class Scene; }

namespace actors
{
	namespace characters
	{
		class MBox : public Actor
		{
		public:
			MBox(scenes::Scene* scene);
			~MBox();
			col::CircleComponent* GetCircle() override { return mCircle; }
			components::RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
			void ActorInput(const uint8_t* keyState) override;
			void UpdateActor(float deltaTime) override;
		private:
			col::CircleComponent* mCircle;
			components::RigidbodyComponent* mRigidbody;
		};
	}
}
