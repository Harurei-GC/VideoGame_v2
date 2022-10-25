#pragma once
#include "components/Component.h"

namespace actors
{
	namespace characters
	{
		class Player;
	}
}
namespace objects { class ActorObjects; }

namespace ch = actors::characters;

namespace components
{
	enum class EnemyState
	{
		Stroll,	// 徘徊
		Attack, // 攻撃
		Rest	// 休憩
	};

	class AIComponent :public Component
	{
	public:
		AIComponent(actors::Actor* owner, int updateOrder = 40);
		~AIComponent();
		void Start()override;
		void ProcessInput(const uint8_t* keyState)override;
		void Update(float deltaTime)override;
		void SetEnemyState(EnemyState estate) { mEState = estate; }
		EnemyState GetEnemyState() { return mEState; }
	private:
		void UpdateStroll();	// 巡回中の処理
		void UpdateAttack();	// 攻撃中の処理
		void UpdateRest();		// 休憩中の処理
		EnemyState mEState;

		objects::ActorObjects* mActorObjects;	// Battleから必要なActor::Characterを取得するためのポインタ集合のクラス
		ch::Player* player;
	};
}
