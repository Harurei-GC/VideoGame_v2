#include "Sprite.h"
#include "SpriteComponent.h"
#include "Game.h"

Sprite::Sprite(Game* game)
	:Actor(game)
{
	sprite = new SpriteComponent(this,110);
	// TODO:�������ɂ���
	sprite->SetRenderColorAlpha(100);
	sprite->SetTexture(game->GetTexture("assets/TimerBackground.png"));
}

Sprite::~Sprite()
{
}