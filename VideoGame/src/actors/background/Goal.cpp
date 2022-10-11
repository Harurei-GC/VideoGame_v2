#include "scenes/Scene.h"
#include "actors/background/Goal.h"
#include "components/SpriteComponent.h"
#include "components/collider/CircleComponent.h"
#include "actors/characters/MBox.h"
#include "math/Random.h"
#include "math/Math.h"


namespace bg = actors::background;
namespace actors
{
	namespace background
	{
		Goal::Goal(scenes::Scene* scene) 
			:Actor(scene)
		{
			SetRole(Role::Goal);

			components::SpriteComponent* sprite = new components::SpriteComponent(this,80);
			sprite->SetTexture(scene->GetTexture("assets/Goal.png"));
			math::Random* rand = new math::Random();
		}

		void Goal::UpdateActor(float deltaTime)
		{

		}

		void Goal::ActorInput(const uint8_t* keyState)
		{

		}

		// HACK:このクラスじゃなくて別のクラスで部品化したい
		Vector2Int Goal::RandomPosition(managers::MakeDangeon* dangeon)
		{
			Vector2Int position = dangeon->getLastRoomBoxPosition();
			Vector2Int size = dangeon->getLastRoomSize();
			while (true)
			{
				Vector2Int mPosition = { rand->Sampling(position.x, position.x + size.x - 1),rand->Sampling(position.y, position.y + size.y - 1) };
				if (mPosition == position) { continue; }
				return mPosition;
			}

		}

		bool GoalIntersect(const bg::Goal& goal, ch::MBox& box)
		{
			float X = goal.GetPosition().x - box.GetPosition().x;
			if (X < 0) { X = -X; }
			float Y = goal.GetPosition().y - box.GetPosition().y;
			if (Y < 0) { Y = -Y; }
			Vector2 diff = Vector2(X, Y);

			float XY = CHARACHIP_EDGE / 2 + box.GetCircle()->GetRadius();
			Vector2 radiiSq = Vector2(XY, XY);

			return (diff.x <= radiiSq.x) && (diff.y <= radiiSq.y);
		}
	}
}
