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

	// Game����Ăяo�����ProcessInput�֐��i�I�[�o�[���C�h�s�j
	void ProcessInput(const uint8_t* keyState);
	// Game����Ăяo�����Update�֐��i�I�[�o�[���C�h�s�j
	void Update(float deltaTime);
	// Actor�Ɋ֘A�t����ꂽ�R���|�[�l���g�̍X�V�i�I�[�o�[���C�h�s�j
	void UpdateComponents(float deltaTime);
	// Actor�ŗL�̓��̓R�[�h�i�I�[�o�[���C�h�j
	virtual void ActorInput(const uint8_t* keyState);
	// �eActor�̍X�V����
	virtual void UpdateActor(float deltaTime);

	// �R���|�[�l���g�ǉ�
	void AddComponent(class Component* component);
	// �R���|�[�l���g�폜
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
	// Rotation����Ȃ�����?verticalhorizontal���邩��
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