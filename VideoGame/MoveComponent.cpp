#include "MoveComponent.h"
#include "Component.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Mob.h"
#include "CircleComponent.h"
#include "Player.h"
#include "InputComponent.h"
#include <iostream>
#include "Friend.h"

// 現時点では、PlayerとMob間の閉鎖的な条件でしか成り立たない。
// これを変更して、Player-Enemy、Player-Player間の衝突などを実装する。
// 
//

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mHorizontalSpeed(0.0f)
	,mHorizontalAcceleration(0.0f)
	,mHorizontalForce(0.0f)
	,mVerticalSpeed(0.0f)
	,mVerticalAcceleration(0.0f)
	,mVerticalForce(0.0f)
	,mPowerSpeed(Vector2(0.0f, 0.0f))
	,isPoweredX(false)
	,isPoweredY(false)
{
}

void MoveComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();

	Player* player = mGame->GetPlayer();
	Friend* fri = mGame->GetFriend();
	Mob* mob = mGame->GetMob();

	// 衝突判定
	// Player,Friend
	if (mOwner->GetRole() == Actor::Role::Player)
	{
		if (!Intersect(*(player->GetCircle()), *(mob->GetCircle())))
		{
			AccelMove(deltaTime, pos, mob, player);
		}
		//if (!Intersect(*(player->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, player);
		//}
	}// Mob
	else if (mOwner->GetRole() == Actor::Role::Mob)
	{
		if (!Intersect(*(mob->GetCircle()), *(player->GetCircle())))
		{
			AccelMove(deltaTime, pos, player, mob);
		}
		//if (!Intersect(*(mob->GetCircle()), *(fri->GetCircle())))
		//{
		//	AccelMove(deltaTime, pos, fri, mob);
		//}
	}// Enemy
	else if (mOwner->GetRole() == Actor::Role::Enemy)
	{

	}

	mOwner->SetPosition(pos);
}

// 基本的な移動（等加速度的）
// 物理学にのっとり、力・加速度・速度の3要素で計算
// 摩擦力を考慮し、さらに上限速度も設定している。
//
void MoveComponent::AccelMove(float deltaTime, Vector2& pos, Actor* you, Actor* me)
{ 

	Mob* mob = mGame->GetMob();
	Player* player = mGame->GetPlayer();
	const std::vector<class Vector2>objPosition = mGame->GetObjPosition();


	float negX;
	if(mHorizontalForce <0.0f){ negX = -1.0f; }
	else { negX = 1.0f; }
	// 加速度・速度計算
	mHorizontalAcceleration = negX * mHorizontalForce * mHorizontalForce / me->GetMass();
	mHorizontalSpeed += mHorizontalAcceleration * deltaTime;
	// スピードアップボタン押されているかつ画面端にいなければ加速
	if (isPoweredX && pos.x > 20.0f && pos.x + 20.0f< WIDTH) 
	{ mHorizontalSpeed += negX * mPowerSpeed.x; }
	// 加速度が0のときかつスピードが摩擦力以上であれば摩擦力が作動
	if ((mHorizontalAcceleration == 0 )&& (fabsf(mHorizontalSpeed) > me->GetFriction()))
	{ 
		if(mHorizontalSpeed > 0){mHorizontalSpeed -= me->GetFriction(); }
		else if (mHorizontalSpeed < 0) { mHorizontalSpeed += me->GetFriction(); }
	}
	// スピードが摩擦力より小さければスピードを0にする
	else if ((mHorizontalAcceleration == 0) && (fabsf(mHorizontalSpeed) <= me->GetFriction()))
	{
		mHorizontalSpeed = 0;
	}
	// 上限速度設定(プレイヤーのみ)
	if (me->GetRole() == Actor::Role::Player)
	{
		if (mHorizontalSpeed > 350.0f)
		{
			mHorizontalSpeed = 350.0f;
			if (isPoweredX) { mHorizontalSpeed += negX * mPowerSpeed.x; }
		}
		else if (mHorizontalSpeed < -350.0f)
		{
			mHorizontalSpeed = -350.0f;
			if (isPoweredX) { mHorizontalSpeed += negX * mPowerSpeed.x; }
		}
	}
	pos.x += mHorizontalSpeed * deltaTime;
	// 衝突判定　HACK:書き方冗長
	Vector2 diffX = pos - you->GetPosition();
	float distSqX = diffX.LengthSq();
	float radiiSqX = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqX *= radiiSqX;
	if (distSqX <= radiiSqX)
	{
		pos.x -= mHorizontalSpeed * deltaTime;
		// 衝突した相手に自分のスピードを与える
		if (me->GetRole() == Actor::Role::Mob)
		{
			float playerSpeed = player->GetInput()->GetHorizontalSpeed();
			SwapSpeed(mHorizontalSpeed, playerSpeed);
			player->GetInput()->SetHorizontalSpeed(playerSpeed);
		}
		else if (me->GetRole() == Actor::Role::Player)
		{
			float mobSpeed = mob->GetMove()->GetHorizontalSpeed();
			SwapSpeed(mHorizontalSpeed, mobSpeed);
			mob->GetMove()->SetHorizontalSpeed(mobSpeed);
		}
	}



	float negY;
	if (mVerticalForce < 0.0f) { negY = -1.0f; }
	else { negY = 1.0f; }
	// 加速度・速度計算
	mVerticalAcceleration = negY * mVerticalForce * mVerticalForce / me->GetMass();
	mVerticalSpeed += mVerticalAcceleration * deltaTime;
	// スピードアップボタンが押されているかつ画面端にいなければ加速
	if (isPoweredY && pos.y > 20.0f && pos.y + 20.0f < WIDTH)
	{ mVerticalSpeed += negY * mPowerSpeed.y; }
	// 加速度が０のときかつスピードが摩擦力以上であれば摩擦力が作動
	if ((mVerticalAcceleration == 0) && (fabsf(mVerticalSpeed) > me->GetFriction()))
	{
		if (mVerticalSpeed > 0) { mVerticalSpeed -= me->GetFriction(); }
		else if (mVerticalSpeed < 0) { mVerticalSpeed += me->GetFriction(); }
	}
	// スピードが摩擦力より小さければスピードを0にする
	else if ((mVerticalAcceleration == 0) && (fabsf(mVerticalSpeed) <= me->GetFriction()))
	{
		mVerticalSpeed = 0;
	}
	// 上限速度設定
	if (mVerticalSpeed > 300.0f)
	{ 
		mVerticalSpeed = 300.0f; 
		if(isPoweredY){ mVerticalSpeed += negY * mPowerSpeed.y; }
	}
	else if (mVerticalSpeed < -300.0f) {
		mVerticalSpeed = -300.0f; 
		if (isPoweredY) { mVerticalSpeed += negY * mPowerSpeed.y; }
	}
	pos.y += mVerticalSpeed * deltaTime;
	// 衝突判定　HACK:書き方冗長
	Vector2 diffY = pos - you->GetPosition();
	float distSqY = diffY.LengthSq();
	float radiiSqY = mGame->GetMob()->GetCircle()->GetRadius() + mGame->GetPlayer()->GetCircle()->GetRadius();
	radiiSqY *= radiiSqY;
	if (distSqY <= radiiSqY)
	{
		pos.y -= mVerticalSpeed * deltaTime;
		//衝突した相手に自分のスピードを与える

		if (me->GetRole() == Actor::Role::Mob)
		{
			float playerSpeed = player->GetInput()->GetVerticalSpeed();
			SwapSpeed(mVerticalSpeed, playerSpeed);
			player->GetInput()->SetVerticalSpeed(playerSpeed);
		}
		else if (me->GetRole() == Actor::Role::Player)
		{
			float mobSpeed = mob->GetMove()->GetVerticalSpeed();
			SwapSpeed(mVerticalSpeed, mobSpeed);
			mob->GetMove()->SetVerticalSpeed(mobSpeed);
		}
	}

	float meRadious = 0.0f;
	if (me->GetRole() == Actor::Role::Mob)
	{
		meRadious = mGame->GetMob()->GetCircle()->GetRadius();
	}
	else if (me->GetRole() == Actor::Role::Player)
	{
		meRadious = mGame->GetPlayer()->GetCircle()->GetRadius();
	}
	// 全てのObjectクラスに対して、Actorが重なっていないか判定
	for (int i = 0; i < objPosition.size(); i++)
	{
		if ((objPosition.at(i).x - CHARACHIP_EDGE/2 <= pos.x + meRadious) &&
			(pos.x - meRadious<= objPosition.at(i).x + CHARACHIP_EDGE /2))
		{
			if ((objPosition.at(i).y - CHARACHIP_EDGE/2<= pos.y + meRadious) &&
			(pos.y - meRadious<= objPosition.at(i).y + CHARACHIP_EDGE / 2))
			{
				pos.y -= mVerticalSpeed * deltaTime;
				pos.x -= mHorizontalSpeed * deltaTime;
				// 壁に当たったときにすぐに壁から離れられるようにスピードと力をリセット
				mHorizontalForce = 0.0f;
				mHorizontalSpeed = 0.0f;
				mVerticalForce = 0.0f;
				mVerticalSpeed = 0.0f;
			}
		}

	
	}


	// 壁に当たると反射して、ある一定の力を超えた場合に画面外に出る
	// 左端にあたったとき
	if (0.0f > pos.x)
	{ 
		std::cout << "Mob Out:" << mGame->GetMob()->GetMove()->GetHorizontalSpeed() << std::endl;
		// 画面外に出ていたとしても速度がSCREEN_OUT_FORCEより小さくなれば端に戻る
		if (mHorizontalSpeed > -SCREEN_OUT_SPEED)
		{
			pos.x = 0.0f;
			mHorizontalSpeed = -mHorizontalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}
	// 右端にあたったとき
	else if (pos.x > WIDTH) 
	{
		if (mHorizontalSpeed < SCREEN_OUT_SPEED)
		{
			pos.x = WIDTH; 
			mHorizontalSpeed = -mHorizontalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}

	if (0.0f > pos.y) 
	{ 
		if (mVerticalSpeed > -SCREEN_OUT_SPEED)
		{
			pos.y = 0.0f;
			mVerticalSpeed = -mVerticalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}
	else if (pos.y > HEIGHT) 
	{
		if (mVerticalSpeed < SCREEN_OUT_SPEED)
		{
			pos.y = HEIGHT; 
			mVerticalSpeed = -mVerticalSpeed;
		}
		else
		{
			std::cout << "OUT OF SCREEN" << std::endl;
		}
	}

}

void MoveComponent::SwapSpeed(float& mobSpeed, float& playerSpeed)
{
	float tmp = mobSpeed;
	mobSpeed = playerSpeed;
	playerSpeed = tmp;
}


// 等速度移動ver 消してもいいかも
void MoveComponent::NormalMove(Vector2& pos, Mob* mob, Player* player)
{
	pos.x += mHorizontalSpeed;
	// AT:書き方冗長
	Vector2 diffX = pos - mob->GetPosition();
	float distSqX = diffX.LengthSq();
	float radiiSqX = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqX *= radiiSqX;
	if (distSqX <= radiiSqX)
	{
		pos.x -= mHorizontalSpeed;
	}

	pos.y += mVerticalSpeed;
	// AT:書き方冗長
	Vector2 diffY = pos - mob->GetPosition();
	float distSqY = diffY.LengthSq();
	float radiiSqY = mob->GetCircle()->GetRadius() + player->GetCircle()->GetRadius();
	radiiSqY *= radiiSqY;
	if (distSqY <= radiiSqY)
	{
		pos.y -= mVerticalSpeed;
	}

	if (0.0f > pos.x) { pos.x = 0.0f; }
	else if (pos.x > WIDTH) { pos.x = WIDTH; }

	if (0.0f > pos.y) { pos.y = 0.0f; }
	else if (pos.y > HEIGHT) { pos.y = HEIGHT; }
}
