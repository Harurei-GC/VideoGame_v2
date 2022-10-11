#pragma once
#include "Actor.h"

namespace visitors
{
	class Visitor;
}

// TODO:もしかしたらこれから敵の種類が増えたときにEnemyの派生クラスが出てくるかも
class Enemy :public Actor
{
public:
	Enemy(class Scene* scene,Vector2 pos);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	Vector2 GetInitialPosition() const { return mInitialPosition; }
	class CircleComponent* GetCircle() override { return mCircle; }
	class RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
	void TakeDamage(int damage)override { mHP -= damage; }
	void AcceptVisitor(visitors::Visitor* visitor)override;
private:
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	class AIComponent* mAI;
	Vector2 mInitialPosition;
};