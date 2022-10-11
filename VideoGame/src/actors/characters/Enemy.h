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
		// TODO:�����������炱�ꂩ��G�̎�ނ��������Ƃ���Enemy�̔h���N���X���o�Ă��邩��
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
