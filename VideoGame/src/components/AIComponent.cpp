#include "components/AIComponent.h"
#include "actors/Actor.h"
#include "components/Component.h"
#include "scenes/Scene.h"
#include "objects/ActorObjects.h"
#include <iostream>
#include "actors/characters/Player.h"

namespace components
{
	AIComponent::AIComponent(actors::Actor* owner, int updateOrder)
		:Component(owner, updateOrder)
		,mEState(EnemyState::Stroll)
	{
		mActorObjects = owner->GetScene()->GetActorObjects();
	}

	AIComponent::~AIComponent()
	{

	}

	void AIComponent::Start()
	{
		player = mActorObjects->player;
		// NULL値チェック
		if (player == nullptr)
		{
			// @todo 例外
		}
	}

	void AIComponent::ProcessInput(const uint8_t* keyState)
	{
		//　もしplayerと同じ部屋にいれば、Attackへ切り替え
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

	}

	// 攻撃中の処理
	void AIComponent::UpdateAttack()
	{

	}

	// 休憩中の処理
	void AIComponent::UpdateRest()
	{

	}

	/* End of Update Functions */
}
