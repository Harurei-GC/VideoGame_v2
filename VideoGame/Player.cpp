#include "Player.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Mob.h"

Player::Player(Game* game)
	:Actor(game)
{
	SetRole(Role::Player);
	SetMass(5.0f);
	SetFriction(10.0f);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("assets/Player.png"));


	mCircle = new CircleComponent(this);
	mCircle->SetRadius(10.0f);

	mInput = new InputComponent(this);
	mInput->SetForwardKey(SDL_SCANCODE_W);
	mInput->SetBackKey(SDL_SCANCODE_S);
	mInput->SetRightKey(SDL_SCANCODE_D);
	mInput->SetLeftKey(SDL_SCANCODE_A);
	mInput->SetPowerKey(SDL_SCANCODE_SPACE);
	//‰½‚ÅÁ‚µ‚½‚Á‚¯
	//mInput->SetMaxSpeed(10.0f);
	mInput->SetMaxForce(60.0f);
	mInput->SetPowerSpeed(Vector2(200.0f,200.0f));
}

Player::~Player()
{

}

void Player::UpdateActor(float deltaTime)
{

}

void Player::ActorInput(const uint8_t* keyState)
{

}