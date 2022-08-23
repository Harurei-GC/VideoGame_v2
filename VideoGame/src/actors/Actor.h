#pragma once
#include <cstdint>
#include <vector>
#include "../Math.h"

class Actor
{
public:
	enum class State
	{
		Active,
		Paused,
		Dead
	};

	enum class Role
	{
		Player,
		Friend,
		Mob,
		Enemy,
		Object,
		Goal
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Start();
	void ProcessInput(const uint8_t* keyState);
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	// 更新順はActorInput→UpdateActor
	virtual void ActorInput(const uint8_t* keyState);
	virtual void UpdateActor(float deltaTime);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	State GetState() const { return mState; }
	void SetState(State state){ mState = state; }
	float GetMass() const { return mMass; }
	void SetMass(float mass) { mMass = mass; }
	float GetFriction() const { return mFriction; }
	void SetFriction(float friction) { mFriction = friction; }
	Role GetRole() const { return mRole; }
	void SetRole(Role role) { mRole = role; }
	// NOTE:Rotationいらないかも?verticalhorizontalあるから
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	int GetID() const { return IDNo; }
	void SetID(int num) { IDNo = num; }
	int GetHP() const { return mHP; }
	void SetHP(int hp) { mHP = hp; }
	void TakeDamage(int damage) { mHP -= damage; }
	virtual class CircleComponent* GetCircle() { return nullptr; }
	virtual class RigidbodyComponent* GetRigidbody() { return nullptr; }

	class Game* GetGame() { return mGame; }

protected:
	class Game* mGame;

private:
	int mHP;
	// 0から始まる識別番号、Enemyのように複数あるオブジェクト用
	int IDNo;
	State mState;
	Role mRole;
	std::vector<class Component*> mComponents;

	float mScale;
	Vector2 mPosition;
	float mRotation;

	float mMass;
	float mFriction;
};