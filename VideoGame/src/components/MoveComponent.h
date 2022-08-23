#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>
#include "Actor.h"
#include <map>
#include <iostream>

struct Physics
{
	float mass;
	float friction;
};

struct TmpActorStatus
{
	Vector2 position;
	Vector2 speed;
	Vector2 acceleration;
	Vector2 force;
	Actor::Role role;
	Vector2 powerSpeed;
	float radius;
};

class MoveComponent :public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 50);
	void Start() override;
	void Update(float deltaTime) override;


	Vector2 GetSpeed() const { return mSpeed; }
	Vector2 GetAcceleration() const { return mAcceleration; }
	Vector2 GetForce()const { return mForce; }
	Vector2 GetPowerSpeed() const { return mPowerSpeed; }
	void SetSpeed(Vector2 speed) { mSpeed = speed; }
	void SetTmpSpeed(Vector2 speed) { tmpSpeed = speed; }
	void SetAcceleration(Vector2 acceleration) { mAcceleration = acceleration; }
	void SetForce(Vector2 force) { mForce = force; }
	void SetPowerSpeed(Vector2 speed){ mPowerSpeed = speed; }

protected:
	bool isPowered;

private:
	// 等加速度で移動(Update()中で使用) CHANGED:publicからprivateへ移動
	void JudgeActorsCollision(float deltaTime, class Actor* you, class Actor* me, TmpActorStatus& tYou);
	// 等速度移動　消してもいいかも
	// void NormalMove(Vector2& pos, class Mob* mob, class Player* player);
	// 移動ステータス決定
	void meetMoveConditions(float deltaTime);
	// 全てのObjectクラスに対して、Actorが重なっていないか判定
	void JudgeBoxCollisionWithObject(float deltaTime);
	void JudgeCircleCollision(float deltaTime, class Actor* you, class Actor* me, char axis);
	template<typename T>void SwapSpeed(T& aSpeed, T& bSpeed);
	void SetTmpActorStatus(const TmpActorStatus& you);


	// 関数内で一時的に使用する変数
	class Player* player;
	class Friend* fri;
	class Mob* mob;
	std::map<int, class Enemy*> enemy;
	std::vector<class Vector2>objPosition;
	TmpActorStatus tPlayer;
	TmpActorStatus tFriend;
	TmpActorStatus tMob;
	TmpActorStatus tyou;
	TmpActorStatus tEnemy;
	Physics mePhy;
	Vector2 replacePos;
	Actor::Role mRole;
	float mRadius;

	// MoveComponentで保持する値
	Vector2 mSpeed;
	Vector2 tmpSpeed;
	Vector2 mAcceleration;
	Vector2 mForce;
	Vector2 mPowerSpeed;
};