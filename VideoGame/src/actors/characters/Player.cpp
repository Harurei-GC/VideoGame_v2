#include "actors/characters/Player.h"
#include "components/SpriteComponent.h"
#include "scenes/Scene.h"
#include "components/InputComponent.h"
#include "components/collider/CircleComponent.h"
#include "components/RigidbodyComponent.h"
#include "data/KeyData.h"

namespace actors
{
	namespace characters
	{
		Player::Player(scenes::Scene* scene)
			:Actor(scene)
		{
			mKeyData = mScene->GetGame()->GetKeyData();
			SetRole(Role::Player);
			SetMass(5.0f);
			SetFriction(10.0f);

			components::SpriteComponent* sprite = new components::SpriteComponent(this);
			sprite->SetTexture(scene->GetTexture("assets/Player.png"));

			mCircle = new col::CircleComponent(this);
			mCircle->SetRadius(9.0f);

			mRigidbody = new components::RigidbodyComponent(this, mCircle);
			mRigidbody->SetPowerSpeed(Vector2(200.0f,200.0f));

			mInput = new components::InputComponent(this);
			mInput->SetMaxForce(60.0f);
			// @note 削除予定
			//mInput->SetPowerKey(SDL_SCANCODE_SPACE);
		}

		Player::~Player()
		{
			SetState(Actor::State::Dead);
		}

		void Player::ActorStart()
		{
			mInput->SetUpKey(mKeyData->GetUpKey().Getter());
			mInput->SetDownKey(mKeyData->GetDownKey().Getter());
			mInput->SetRightKey(mKeyData->GetRightKey().Getter());
			mInput->SetLeftKey(mKeyData->GetLeftKey().Getter());
		}

		void Player::ActorInput(const uint8_t* keyState)
		{

		}

		void Player::UpdateActor(float deltaTime)
		{
			if (GetHP() <= 0) { SetState(State::Dead); }
		}

	}
}
