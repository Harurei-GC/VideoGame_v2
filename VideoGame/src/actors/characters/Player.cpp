#include "actors/characters/Player.h"
#include "components/SpriteComponent.h"
#include "scenes/Scene.h"
#include "components/InputComponent.h"
#include "components/collider/CircleComponent.h"
#include "components/RigidbodyComponent.h"


namespace actors
{
	namespace characters
	{
		Player::Player(scenes::Scene* scene)
			:Actor(scene)
		{
			SetRole(Role::Player);
			SetMass(5.0f);
			SetFriction(10.0f);

			components::SpriteComponent* sprite = new components::SpriteComponent(this);
			sprite->SetTexture(scene->GetTexture("assets/Player.png"));


			mCircle = new col::CircleComponent(this);
			mCircle->SetRadius(10.0f);

			mRigidbody = new components::RigidbodyComponent(this, mCircle);
			mRigidbody->SetPowerSpeed(Vector2(200.0f,200.0f));

			mInput = new components::InputComponent(this);
			mInput->SetForwardKey(SDL_SCANCODE_W);
			mInput->SetBackKey(SDL_SCANCODE_S);
			mInput->SetRightKey(SDL_SCANCODE_D);
			mInput->SetLeftKey(SDL_SCANCODE_A);
			mInput->SetPowerKey(SDL_SCANCODE_SPACE);
			mInput->SetMaxForce(60.0f);
		}

		Player::~Player()
		{
			SetState(Actor::State::Dead);
		}

		void Player::UpdateActor(float deltaTime)
		{
			if (GetHP() <= 0) { SetState(State::Dead); }
		}

		void Player::ActorInput(const uint8_t* keyState)
		{

		}
	}
}
