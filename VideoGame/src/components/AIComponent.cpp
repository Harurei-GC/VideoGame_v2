#include "components/AIComponent.h"
#include "actors/Actor.h"
#include "components/Component.h"
#include "scenes/Scene.h"
#include "message/ActorMessage.h"
#include <iostream>
#include "actors/characters/Player.h"
#include "managers/MakeDangeon.h"
#include "message/ManagerMessage.h"

namespace components
{
	AIComponent::AIComponent(actors::Actor* owner, int updateOrder)
		:Component(owner, updateOrder)
		,mEState(EnemyState::Stroll)
	{
	}

	AIComponent::~AIComponent()
	{

	}

	void AIComponent::Start()
	{
		mActorMessage = mOwner->GetScene()->GetActorMessage();
		makeDangeon = mOwner->GetScene()->GetManagerMessage()->makeDangeon;
		mRigidbody = mOwner->GetRigidbody();
		player = mActorMessage->player;
		// NULL値チェック
		if (player == nullptr)
		{
			// @todo 例外
		}
	}

	void AIComponent::ProcessInput(const uint8_t* keyState)
	{
		// もしplayerと同じ部屋にいれば、Attackへ切り替え
		// そうでない場合はStrollへ切り替え
		Vector2 ppos = mActorMessage->player->GetPosition();
		Vector2Int plr = makeDangeon->WhereInRoom(static_cast<int>(ppos.x), static_cast<int>(ppos.y));
		Vector2Int enm = makeDangeon->WhereInRoom(static_cast<int>(mOwner->GetPosition().x), static_cast<int>(mOwner->GetPosition().y));
		
		if (plr == enm)// playerとenemyは同じ部屋か
		{
			// playerが部屋にいるなら実行
			if (!(plr == Vector2Int{ -1,-1 })) 
			{
				mEState = EnemyState::Attack;
			}
			else// playerが廊下にいるなら
			{
				mEState = EnemyState::Stroll;
			}
		}
		else// 違う部屋ならば
		{
			mEState = EnemyState::Stroll;
		}
	}

	void AIComponent::Update(float deltaTime)
	{
		if (mEState == EnemyState::Stroll)
		{
			UpdateStroll();
		}
		else if (mEState == EnemyState::Attack)
		{
			UpdateAttack();
		}
		else if (mEState == EnemyState::Rest)
		{
			UpdateRest();
		}
	}

	/* Update Functions */

	// 巡回中の処理
	void AIComponent::UpdateStroll()
	{
		// playerと同じforceを受ける
		mRigidbody->SetForce((player->GetRigidbody()->GetForce())*0.8f);
	}

	// 攻撃中の処理
	void AIComponent::UpdateAttack()
	{
		// playerを追いかける
		Vector2 force = player->GetPosition() - mOwner->GetPosition();
		force.Normalize();
		float power = 30.0f;	// Force値調整
		force = Vector2{ force.x * power, force.y * power };
		mRigidbody->SetForce(force);
	}

	// 休憩中の処理
	void AIComponent::UpdateRest()
	{
		// 休憩中は停止する
		mRigidbody->SetSpeed(Vector2{ 0.0f, 0.0f });
		mRigidbody->SetAcceleration(Vector2{ 0.0f,0.0f });
		mRigidbody->SetForce(Vector2{ 0.0f,0.0f });
	}

	/* End of Update Functions */
}
