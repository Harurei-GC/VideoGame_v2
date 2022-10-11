#pragma once
#include "components/Component.h"
#include "actors/Actor.h"
#include "math/Math.h"

namespace scenes { class Battle; }
namespace components
{
	class RigidbodyComponent : public Component
	{
	public:
		RigidbodyComponent(actors::Actor* owner, col::CircleComponent* circle);
		void Start() override;
		void Update(float deltaTime) override;
		Vector2 GetSpeed() const { return mSpeed; }
		Vector2 GetAcceleration() const { return mAcceleration; }
		Vector2 GetForce() const { return mForce; }
		Vector2 GetPowerSpeed() const { return mPowerSpeed; }
		Vector2 GetReplacePosition() const { return replacePos; }
		void SetSpeed(Vector2 speed) { mSpeed = speed; }
		void SetAcceleration(Vector2 accel) { mAcceleration = accel; }
		void SetForce(Vector2 force) { mForce = force; }
		void SetPowerSpeed(Vector2 powerspeed) { mPowerSpeed = powerspeed; }
		void SetReplacePosition(Vector2 position) { replacePos = position; }
		void SetIsPowered(bool power) { isPowered = power; }
	private:
		void JudgeCollisionWithBlkTree(float deltaTime);
		Vector2 mSpeed;
		Vector2 mAcceleration;
		Vector2 mForce;
		Vector2 mPowerSpeed;
		Vector2 replacePos;
		bool isPowered; // InputComponent�Ȃǂ���ύX�ł���悤�ɂ���
		scenes::Battle* battle;
	};
}
