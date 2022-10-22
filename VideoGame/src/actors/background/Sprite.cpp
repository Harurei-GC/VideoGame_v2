#include "actors/background/Sprite.h"
#include "components/SpriteComponent.h"
#include "scenes/Scene.h"

namespace actors
{
	namespace background
	{
		Sprite::Sprite(scenes::Scene* scene)
			:Actor(scene)
		{
			sprite = new components::SpriteComponent(this,110);
			// TODO:半透明にする
			sprite->SetRenderColorAlpha(100);
			sprite->SetTexture(scene->GetTexture("assets/TimerBackground.png"));
		}

		Sprite::~Sprite()
		{
		}
	}
}
