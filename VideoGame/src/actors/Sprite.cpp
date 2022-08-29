#include "Sprite.h"
#include "../components/SpriteComponent.h"
#include "../scenes/Scene.h"

Sprite::Sprite(Scene* scene)
	:Actor(scene)
{
	sprite = new SpriteComponent(this,110);
	// TODO:”¼“§–¾‚É‚·‚é
	sprite->SetRenderColorAlpha(100);
	sprite->SetTexture(scene->GetTexture("assets/TimerBackground.png"));
}

Sprite::~Sprite()
{
}