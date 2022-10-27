#pragma once
#include "components/Component.h"
#include "components/RigidbodyComponent.h"

namespace actors
{
	namespace characters
	{
		class Player;
	}
}
namespace message { 
	class ActorMessage;
	class ManagerMessage;
	class RigidbodyMessage;
}
namespace managers { class MakeDangeon; }

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

		components::RigidbodyComponent* mRigidbody;
		message::ActorMessage* mActorMessage;	// Battleから必要なActor::Characterを取得するためのポインタ集合のクラス
		managers::MakeDangeon* makeDangeon;	
		ch::Player* player;
	};
}
