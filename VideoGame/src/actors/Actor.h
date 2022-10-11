#pragma once
#include <cstdint>
#include <vector>
#include "../Math.h"
#include "visitors/Visitor.h"

namespace visitors {
	class Visitor; 
}

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

	Actor(class Scene* scene);
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
	
	// visitor受け入れ
	virtual void AcceptVisitor(visitors::Visitor* visitor){}

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
	int GetHP() const { return mHP; }

	virtual void TakeDamage(int damage) {}
	virtual class CircleComponent* GetCircle() { return nullptr; }
	virtual class RigidbodyComponent* GetRigidbody() { return nullptr; }

	class Scene* GetScene() { return mScene; }

protected:
	class Scene* mScene;
	int mHP;

private:
	State mState;
	Role mRole;
	float mScale;
	Vector2 mPosition;
	float mRotation;
	float mMass;
	float mFriction;

	std::vector<class Component*> mComponents;
};