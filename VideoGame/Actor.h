#pragma once
#include <cstdint>
#include <vector>
#include "Math.h"

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
		Mob,
		Enemy,
		Object,
		Goal
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Gameから呼び出されるProcessInput関数（オーバーライド不可）
	void ProcessInput(const uint8_t* keyState);
	// Gameから呼び出されるUpdate関数（オーバーライド不可）
	void Update(float deltaTime);
	// Actorに関連付けられたコンポーネントの更新（オーバーライド不可）
	void UpdateComponents(float deltaTime);
	// Actor固有の入力コード（オーバーライド）
	virtual void ActorInput(const uint8_t* keyState);
	// 各Actorの更新処理
	virtual void UpdateActor(float deltaTime);

	// コンポーネント追加
	void AddComponent(class Component* component);
	// コンポーネント削除
	void RemoveComponent(class Component* component);

	// Getter,Setter
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
	// Rotationいらないかも?verticalhorizontalあるから
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	class Game* GetGame() { return mGame; }

protected:
	class Game* mGame;

private:
	State mState;
	Role mRole;
	std::vector<class Component*> mComponents;

	float mScale;
	Vector2 mPosition;
	float mRotation;

	float mMass;
	float mFriction;
};