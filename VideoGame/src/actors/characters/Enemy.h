#pragma once
#include "actors/characters/CharacterActor.h"

namespace scenes { class Scene; }
namespace visitors
{
	class Visitor;
}
namespace components { class AIComponent; }

namespace actors
{
	namespace characters
	{
		// TODO:‚à‚µ‚©‚µ‚½‚ç‚±‚ê‚©‚ç“G‚Ìí—Ş‚ª‘‚¦‚½‚Æ‚«‚ÉEnemy‚Ì”h¶ƒNƒ‰ƒX‚ªo‚Ä‚­‚é‚©‚à
		class Enemy :public CharacterActor
		{
		public:
			Enemy(scenes::Scene* scene,Vector2 pos);
			~Enemy();
			void UpdateActor(float deltaTime) override;
			Vector2 GetInitialPosition() const { return mInitialPosition; }
			col::CircleComponent* GetCircle() override { return mCircle; }
			components::RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
			void TakeDamage(int damage)override { mHP -= damage; }
			void AcceptVisitor(visitors::Visitor* visitor)override;
		private:
			col::CircleComponent* mCircle;
			components::RigidbodyComponent* mRigidbody;
			components::AIComponent* mAI;
			Vector2 mInitialPosition;
		};
	}
}
