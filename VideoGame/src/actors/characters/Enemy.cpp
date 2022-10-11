#include "actors/characters/Enemy.h"
#include "scenes/Scene.h"
#include "components/SpriteComponent.h"
#include "components/collider/CircleComponent.h"
#include "components/AIComponent.h"
#include "components/RigidbodyComponent.h"
#include <iostream>
#include "visitors/Visitor.h"


namespace actors
{
	namespace characters
	{
		Enemy::Enemy(scenes::Scene* scene, Vector2 pos)
			:CharacterActor(scene)
			,mInitialPosition(pos)
		{
			SetRole(Role::Enemy);
			SetMass(10.0f);
			SetFriction(10.0f);
			SetPosition(mInitialPosition);

			components::SpriteComponent* sprite = new components::SpriteComponent(this);
			sprite->SetTexture(mScene->GetTexture("assets/Snake.png"));

			mCircle = new col::CircleComponent(this);
			mCircle->SetRadius(10.0f);

			mRigidbody = new components::RigidbodyComponent(this, mCircle);

			mAI = new components::AIComponent(this);

		}

		Enemy::~Enemy()
		{
		}

		void Enemy::UpdateActor(float deltaTime)
		{
			if (GetHP() <= 0) { SetState(State::Dead); }
		}

		void Enemy::AcceptVisitor(visitors::Visitor* visitor)
		{
			visitor->VstEnemy(this);
		}
	}
}
