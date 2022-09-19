#pragma once
#include "Actor.h"

// TODO:‚à‚µ‚©‚µ‚½‚ç‚±‚ê‚©‚ç“G‚Ìí—Ş‚ª‘‚¦‚½‚Æ‚«‚ÉEnemy‚Ì”h¶ƒNƒ‰ƒX‚ªo‚Ä‚­‚é‚©‚à
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
private:
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	class AIComponent* mAI;
	Vector2 mInitialPosition;
};