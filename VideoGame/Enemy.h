#pragma once
#include "Actor.h"
//#include "MoveComponent.h"

// TODO:‚à‚µ‚©‚µ‚½‚ç‚±‚ê‚©‚ç“G‚Ìí—Ş‚ª‘‚¦‚½‚Æ‚«‚ÉEnemy‚Ì”h¶ƒNƒ‰ƒX‚ªo‚Ä‚­‚é‚©‚à
class Enemy :public Actor
{
public:
	Enemy(class Game* game,Vector2 pos,int number);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	Vector2 GetInitialPosition() const { return mPosition; }
	//TmpActorStatus GetTmpActorStatus() const { return mStatus; }
	class CircleComponent* GetCircle() override { return mCircle; }
	class RigidbodyComponent* GetRigidbody() override { return mRigidbody; }
	//class MoveComponent* GetMove() const { return mMove; }
private:
	class CircleComponent* mCircle;
	class RigidbodyComponent* mRigidbody;
	//class MoveComponent* mMove;
	class AIComponent* mAI;
	Vector2 mPosition;
	//TmpActorStatus mStatus;
};