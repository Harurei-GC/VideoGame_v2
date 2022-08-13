#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent :public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 50);
	void Update(float deltaTime) override;

	// 等速度移動　消してもいいかも
	void NormalMove(Vector2& pos, class Mob* mob, class Player* player);
	// 等加速度で移動(Update()中で使用)
	void AccelMove(float deltaTime, Vector2& pos, class Actor* you, class Actor* me);
	void SwapSpeed(float& mobSpeed, float& playerSpeed);
	
	float GetVerticalSpeed() const { return mVerticalSpeed; }
	float GetHorizontalSpeed() const { return mHorizontalSpeed; }
	Vector2 GetPowerSpeed() const { return mPowerSpeed; }
	float GetVerticalForce() const { return mVerticalForce; }
	float GetHorizontalForce() const { return mHorizontalForce; }
	void SetVerticalSpeed(float speed) { mVerticalSpeed = speed; }
	void SetHorizontalSpeed(float speed) { mHorizontalSpeed = speed; }
	void SetPowerSpeed(Vector2 speed){ mPowerSpeed = speed; }
	void SetVerticalForce(float force) { mVerticalForce = force; }
	void SetHorizontalForce(float force) { mHorizontalForce = force; }

protected:
	// スピードアップボタンが押されたかどうか
	bool isPoweredX;
	bool isPoweredY;

private:
	// AT:float型ではなくVector2型で水平垂直まとめられるのでは？
	// 水平方向スピード
	float mHorizontalSpeed;
	// 水平方向加速度
	float mHorizontalAcceleration;
	// 水平方向に加わる力
	float mHorizontalForce;
	// 垂直方向スピード
	float mVerticalSpeed;
	// 垂直方向加速度
	float mVerticalAcceleration;
	// 垂直方向に加わる力
	float mVerticalForce;
	// スピードアップボタン押したときの追加速度
	Vector2 mPowerSpeed;
};