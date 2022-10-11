#pragma once
#include "actors/Actor.h"


namespace scenes { class Scene; }
namespace components
{
	class RigidbodyComponent;
	class InputComponent;
	namespace collider
	{
		class CircleComponent;
	}
}

namespace col = components::collider;

namespace actors
{
	namespace characters
	{
		class Player :public Actor
		{
		public:
			Player(scenes::Scene* scene);
			~Player();
			void ActorInput(const uint8_t* keyState) override;
			void UpdateActor(float deltaTime) override;
			col::CircleComponent* GetCircle() { return mCircle; }
			components::RigidbodyComponent* GetRigidbody() { return mRigidbody; }
			components::InputComponent* GetInput() { return mInput; }
		private:
			col::CircleComponent* mCircle;
			components::RigidbodyComponent* mRigidbody;
			components::InputComponent* mInput;
		};
	}
}
