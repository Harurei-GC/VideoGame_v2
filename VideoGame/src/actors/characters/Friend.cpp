#include "actors/characters/Friend.h"
#include "scenes/Scene.h"
#include "components/SpriteComponent.h"
#include "components/collider/CircleComponent.h"
#include "components/AIComponent.h"
#include "components/RigidbodyComponent.h"


namespace actors
{
	namespace characters
	{
		Friend::Friend(scenes::Scene* scene)
			:Actor(scene)
		{

			SetRole(Role::Friend);
			SetMass(5.0f);
			SetFriction(10.0f);

			sprite = new components::SpriteComponent(this);
			sprite->SetTexture(scene->GetTexture("assets/Friend.png"));

			mCircle = new col::CircleComponent(this);
			mCircle->SetRadius(10.0f);

			mRigidbody = new components::RigidbodyComponent(this, mCircle);

			//mMove = new MoveComponent(this);

			mAI = new components::AIComponent(this);
		}

		Friend::~Friend()
		{
	
		}

		void Friend::UpdateActor(float deltaTime)
		{

		}

		void Friend::ActorInput(const uint8_t* keyState)
		{

		}
	}
}
