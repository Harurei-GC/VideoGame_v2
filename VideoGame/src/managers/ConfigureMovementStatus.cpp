#include "scenes/ScnBattle.h"
#include "managers/ConfigureMovementStatus.h"
#include "actors/background/BlockTree.h"
#include "actors/Actor.h"
#include "actors/characters/Player.h"
#include "actors/characters/Friend.h"
#include "actors/characters/MBox.h"
#include "actors/characters/Enemy.h"
#include <iostream>
#include "components/RigidbodyComponent.h"
#include "components/collider/CircleComponent.h"

#define DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_ // 一時的にfriend消去

namespace managers
{
	ConfigureMovementStatus::ConfigureMovementStatus(scenes::ScnBattle* battle)
		:cBattle(battle)
		,player(nullptr)
		,mbox(nullptr)
	{
	}

	void ConfigureMovementStatus::Start()
	{
		player = cBattle->GetPlayer();
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
		fri = cBattle->GetFriend();
	#endif
		mbox = cBattle->GetMBox();
		enemy = cBattle->GetEnemiesMap();
	}

	void ConfigureMovementStatus::Update(float deltaTime)
	{
		bool isEnemyDamaged[ENEMIES] = { 0 };

		Dim2 dim;
		for (int i = 0; i < 2; i++)
		{
			(i == 0) ? dim = Dim2::x : dim = Dim2::y;
			// player視点
			// NOTE:既にRigidbodyで次フレームの座標を計算済みであるから、基本的にその座標であるReplacePositionを使う。
			if (Intersect(player->GetCircle()->GetRadius(), mbox->GetCircle()->GetRadius()
				, player->GetRigidbody()->GetReplacePosition(), mbox->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, mbox, player,-1, dim);
			}
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
			if (Intersect(player->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
				, player->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, fri, player,-1, dim);
			}
			// friend視点
			if (Intersect(fri->GetCircle()->GetRadius(), mbox->GetCircle()->GetRadius()
				, fri->GetRigidbody()->GetReplacePosition(), mbox->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, mbox, fri,-1, dim);
			}
			if (Intersect(fri->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
				, fri->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, player, fri,-1, dim);
			}
	#endif
			// mbox視点
			if (Intersect(mbox->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
				, mbox->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, player, mbox,-1, dim);
			}
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
			if (Intersect(mbox->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
				, mbox->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, fri, mbox,-1, dim);
			}
	#endif

			// enemyに関連する処理
			for (int j = 0; j < ENEMIES; j++)
			{
				// キーjが指す要素が残っていれば判定
				if (enemy.find(j) != enemy.end())
				{
					// WARNING:y方向に衝突すると、x軸の場合とy軸の場合の2回条件式がくりかえされる
					if (Intersect(enemy.at(j)->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
						, enemy.at(j)->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
					{
						isEnemyDamaged[j] = IsMeDamaged(player->GetRigidbody()->GetSpeed(),enemy.at(j)->GetRigidbody()->GetSpeed(),
							player->GetRigidbody()->GetReplacePosition(), enemy.at(j)->GetRigidbody()->GetReplacePosition());
						// WARNING:この関数はPlayer視点。enemyとplayerの引数を逆にすると挙動がおかしくなる。
						// Player視点の条件分岐に持っていこうにも、enemyを識別することが出来なくなる。なのでここに置いておく。
						JudgeActorsCollision(deltaTime, enemy.at(j),player, j, dim);
					}
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
					if (Intersect(enemy.at(j)->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
						, enemy.at(j)->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
					{
						isEnemyDamaged[j] = IsMeDamaged();
						JudgeActorsCollision(deltaTime, enemy.at(j), fri, j, dim);
					}
	#endif
				}
			}
		}

		// ダメージを与えるための処理
		// NOTE:他の処理と切り離すことで、1フレーム内でダメージが足し算される事を防ぐ
		for (int i = 0; i < ENEMIES; i++)
		{
			if (isEnemyDamaged[i])
			{
				enemy.at(i)->TakeDamage(50);
			}
		}
	}

	bool ConfigureMovementStatus::Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos)
	{
		Vector2 diff = apos - bpos;
		float distSq = diff.LengthSq();
		float radiiSq = arad + brad;
		radiiSq *= radiiSq;
		return distSq <= radiiSq;
	}

	void ConfigureMovementStatus::JudgeActorsCollision(float deltaTime,actors::Actor* you, actors::Actor* me,int ID, Dim2 axis)
	{
		Vector2 position;
		Vector2 meSpeed;
		Vector2 youSpeed;
		position = me->GetRigidbody()->GetReplacePosition();
		meSpeed = me->GetRigidbody()->GetSpeed();
		youSpeed = you->GetRigidbody()->GetSpeed();
	
		// 衝突判定
		// meはReplacePosition、youは現在のPosition
		if (Intersect(me->GetCircle()->GetRadius(),you->GetCircle()->GetRadius(),me->GetRigidbody()->GetReplacePosition(),you->GetPosition()))
		{
			switch (axis)
			{
			case Dim2::x:
				position.x -= meSpeed.x * deltaTime;
				SwapSpeed(meSpeed.x, youSpeed.x);
				break;
			case Dim2::y:
				position.y -= meSpeed.y * deltaTime;
				SwapSpeed(meSpeed.y, youSpeed.y);
				break;
			default:
				break;
			}
			me->GetRigidbody()->SetReplacePosition(position);
			me->GetRigidbody()->SetSpeed(meSpeed);
			switch (you->GetRole())
			{
			case actors::Actor::Role::MBox:
				mbox->GetRigidbody()->SetSpeed(youSpeed);
				break;
			case actors::Actor::Role::Player:
				player->GetRigidbody()->SetSpeed(youSpeed);
				break;
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
			case actors::Actor::Role::Friend:
				fri->GetRigidbody()->SetSpeed(youSpeed);
				break;
	#endif
			case actors::Actor::Role::Enemy:
				enemy.at(ID)->GetRigidbody()->SetSpeed(youSpeed);
				break;
			default:
				break;
			}
		}
	}

	template<typename T>
	void ConfigureMovementStatus::SwapSpeed(T& aSpeed, T& bSpeed)
	{
		T tmp = aSpeed;
		aSpeed = bSpeed;
		bSpeed = tmp;
	}

	// NOTE:ScnBattle.cppで呼び出す
	void ConfigureMovementStatus::SetActorsPosition()
	{
		player->SetPosition(player->GetRigidbody()->GetReplacePosition());
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
		fri->SetPosition(fri->GetRigidbody()->GetReplacePosition());
	#endif
		mbox->SetPosition(mbox->GetRigidbody()->GetReplacePosition());
		for (auto iter = enemy.begin(); iter != enemy.end(); ++iter)
		{
			iter->second->SetPosition(iter->second->GetRigidbody()->GetReplacePosition());
		}
	}

	bool ConfigureMovementStatus::IsMeDamaged(Vector2 youSpeed, Vector2 meSpeed, Vector2 youPos, Vector2 mePos)
	{
		// Me側のダメージを計算する。
		// Meの後方からYouが衝突してきた場合にダメージを与える。
		// MeやYouはcharactersのいずれかである。
		//

		if ((youSpeed.x == 0.0f)&&(youSpeed.y == 0.0f))
		{// 衝突先の相手の速度が０（動いていない）ならば、meにダメージは入らない
			return false;
		}
		else if ((meSpeed.x == 0.0f) && (meSpeed.y == 0.0f) )
		{// 衝突時meの速度が０（動いていない）ならば、ダメージ受ける
			return true;
		}

		// 速度の内積を計算し、符号が正だった場合ダメージ判定が生じる
		if (Vector2::Dot(youSpeed, meSpeed) < 0)
		{// 負の場合＝正面衝突＝ダメージはなし
			return false;
		}
		else
		{// 正の場合
			// youとmeどちらが前方にいるか判定し、meが前方にいる場合にダメージ入れる。
			// そのために、youPosから見たmePosへの方向ベクトルの符号と、youSpeedの方向ベクトルの符号を比較する。
			// x軸とy軸それぞれ符号が同じならば、meはyouよりも前方にいることとなる。
			Vector2Int sign = Vector2Int{ int(mePos.x - youPos.x), int(mePos.y - youPos.y) };
			// NOTE:0除算防止のため場合分け
			sign = Vector2Int{ (sign.x == 0.0f)?0:(sign.x / std::abs(sign.x))
				, (sign.y==0.0f)?0:(sign.y / std::abs(sign.y)) };
			Vector2Int speed = Vector2Int{ (youSpeed.x == 0.0f) ? 0 : (int(youSpeed.x / std::abs(youSpeed.x))) 
				,(youSpeed.y == 0.0f)?0: (int(youSpeed.y / std::abs(youSpeed.y))) };
			if ((sign.x == speed.x) && (sign.y == speed.y))
			{// youから見てmeがyouの進行方向にいる場合＝meはダメージ受ける
				return true;
			}
			else
			{// ダメージは入らない
				return false;
			}
		}
	}
}