#pragma once
#include "actors/Actor.h"


namespace scenes { class Scene; }
namespace components { class SpriteComponent; }

namespace actors
{
	namespace background
	{
		class Sprite :public Actor
		{
		public:
			Sprite(scenes::Scene* scene);
			~Sprite();
		private:
			components::SpriteComponent* sprite;
		};
	}
}
