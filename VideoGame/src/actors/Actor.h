#pragma once
#include <cstdint>
#include <vector>
#include "math/Math.h"

namespace scenes { class Scene; }
namespace visitors {
	class Visitor; 
}
namespace components { 
	class Component;
	class RigidbodyComponent;
	namespace collider
	{
		class CircleComponent; 
	}
}

namespace col = components::collider;

namespace actors
{
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
			MBox,
			Enemy,
			BlockTree,
			Goal
		};

		Actor(scenes::Scene* scene);
		virtual ~Actor();

		void Start();
		void ProcessInput(const uint8_t* keyState);
		void Update(float deltaTime);
		void UpdateComponents(float deltaTime);
		// çXêVèáÇÕActorInputÅ®UpdateActor
		virtual void ActorInput(const uint8_t* keyState);
		virtual void UpdateActor(float deltaTime);

		void AddComponent(components::Component* component);
		void RemoveComponent(components::Component* component);
	
		// visitoréÛÇØì¸ÇÍ
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
		// NOTE:RotationÇ¢ÇÁÇ»Ç¢Ç©Ç‡?verticalhorizontalÇ†ÇÈÇ©ÇÁ
		float GetRotation() const { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; }
		int GetHP() const { return mHP; }

		virtual void TakeDamage(int damage) {}
		virtual col::CircleComponent* GetCircle() { return nullptr; }
		virtual components::RigidbodyComponent* GetRigidbody() { return nullptr; }

		scenes::Scene* GetScene() { return mScene; }

	protected:
		scenes::Scene* mScene;
		int mHP;

	private:
		State mState;
		Role mRole;
		float mScale;
		Vector2 mPosition;
		float mRotation;
		float mMass;
		float mFriction;

		std::vector<components::Component*> mComponents;
	};
}
