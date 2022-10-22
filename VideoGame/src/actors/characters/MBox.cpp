// @todo 名前をMBoxにリネームしたい

#include "actors/characters/MBox.h"
#include "components/SpriteComponent.h"
#include "scenes/Scene.h"
#include "components/collider/CircleComponent.h"
#include "components/RigidbodyComponent.h"

namespace actors
{
	namespace characters
	{
		MBox::MBox(scenes::Scene* scene)
			:Actor(scene)
		{
			SetRole(Role::MBox);
			SetMass(10.0f);
			SetFriction(10.0f);

			components::SpriteComponent* sprite = new components::SpriteComponent(this,90);
			sprite->SetTexture(scene->GetTexture("assets/Mob.png"));

			mCircle = new col::CircleComponent(this);
			mCircle->SetRadius(8.5f);

			mRigidbody = new components::RigidbodyComponent(this, mCircle);

			//mMove = new MoveComponent(this);
		}

		MBox::~MBox()
		{
		}

		void MBox::UpdateActor(float deltaTime)
		{

		}

		void MBox::ActorInput(const uint8_t* keyState)
		{

		}
	}
}
