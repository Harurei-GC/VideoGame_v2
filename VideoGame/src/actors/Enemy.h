#pragma once
#include "Actor.h"

// TODO:もしかしたらこれから敵の種類が増えたときにEnemyの派生クラスが出てくるかも
class Enemy :public Actor
{
public:
	Enemy(class Scene* scene,Vector2 pos,int number);
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