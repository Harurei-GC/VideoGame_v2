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

#define DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_ // @todo friendは消去して使わない

namespace managers
{

	ConfigureMovementStatus::ConfigureMovementStatus(scenes::ScnBattle* battle)
		:cBattle(battle)
		,player(nullptr)
		,mbox(nullptr)
	{
		for (int i = 0; i < ENEMIES; i++)
		{
			wasPlayerEnemyCorrided.emplace(i, false);
		}
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
		// 一時変数作成
		// radius
		float playerRad = player->GetCircle()->GetRadius();
		float boxRad = mbox->GetCircle()->GetRadius();
		std::map<int, float> enemyRad;
		// position
		Vector2 playerPos = player->GetRigidbody()->GetReplacePosition();
		Vector2 boxPos = mbox->GetRigidbody()->GetReplacePosition();
		std::map<int, Vector2> enemyPos;
		// speed
		Vector2 playerSpd = player->GetRigidbody()->GetSpeed();
		std::map<int, Vector2> enemySpd;
		std::map<int, bool> PECorride;
		// enemy代入
		for (int i = 0; i < ENEMIES; i++)
		{
			PECorride.emplace(i, false);
			if (enemy.find(i) != enemy.end())
			{
				enemyRad.emplace(i, enemy.at(i)->GetCircle()->GetRadius());
				enemyPos.emplace(i, enemy.at(i)->GetRigidbody()->GetReplacePosition());
				enemySpd.emplace(i, enemy.at(i)->GetRigidbody()->GetSpeed());
			}
		}

		bool isEnemyDamaged[ENEMIES] = { 0 };	// enemyにダメージが入るか
		bool isPlayerDamaged = false;			// playerにダメージが入るか

		Dim2 axis;
		for (int i = 0; i < 2; i++)// x軸とy軸
		{
			(i == 0) ? axis = Dim2::x : axis = Dim2::y;
			// player視点
			// NOTE:既にRigidbodyで次フレームの座標を計算済みであるから、基本的にその座標であるReplacePositionを使う。
			if(Intersect(playerRad, boxRad, playerPos, boxPos))
			{
				JudgeActorsCollision(deltaTime, mbox, player,-1, axis);
			}
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
			if (Intersect(player->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
				, player->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, fri, player,-1, axis);
			}
			// friend視点
			if (Intersect(fri->GetCircle()->GetRadius(), mbox->GetCircle()->GetRadius()
				, fri->GetRigidbody()->GetReplacePosition(), mbox->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, mbox, fri,-1, axis);
			}
			if (Intersect(fri->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
				, fri->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, player, fri,-1, axis);
			}
	#endif
			// mbox視点
			if(Intersect(boxRad, playerRad, boxPos, playerPos))
			{
				JudgeActorsCollision(deltaTime, player, mbox,-1, axis);
			}
	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
			if (Intersect(mbox->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
				, mbox->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
			{
				JudgeActorsCollision(deltaTime, fri, mbox,-1, axis);
			}
	#endif

			// enemyに関連する処理
			for (int j = 0; j < ENEMIES; j++)
			{
				// キーjが指す個体のenemyが残っていれば判定
				if (enemy.find(j) != enemy.end())
				{
					// playerとの判定
					// WARNING:y方向に衝突すると、x軸の場合とy軸の場合の2回条件式がくりかえされる
					if(Intersect(enemyRad.at(j), playerRad, enemyPos.at(j), playerPos))
					{
						if (!wasPlayerEnemyCorrided.at(j))// 前フレームで接触してなければ
						{
							PECorride.at(j) = true;
							isEnemyDamaged[j] = IsMeDamaged(playerSpd, enemySpd.at(j), playerPos, enemyPos.at(j));
							// ここで前フレームも接触していたかどうか判定
							if (IsMeDamaged(enemySpd.at(j), playerSpd, enemyPos.at(j), playerPos))
							{
								isPlayerDamaged = true;
							}
						}

						// WARNING:この関数はPlayer視点。enemyとplayerの引数を逆にすると挙動がおかしくなる。
						// Player視点の条件分岐に持っていこうにも、enemyを識別することが出来なくなる。なのでここに置いておく。
						//JudgeActorsCollision(deltaTime, enemy.at(j),player, j, axis);
						PlayerEnemyCollision(deltaTime, j, axis);
					}
					else
					{// 今フレームでplayerとenemyが衝突していなければ
						wasPlayerEnemyCorrided.at(j) = false;
					}

					// 他のenemyとの判定
					for (int k = j+1; k < ENEMIES; k++)
					{
						if (enemy.find(k) != enemy.end())
						{
							if (Intersect(enemyRad.at(j), enemyRad.at(k), enemyPos.at(j), enemyPos.at(k)))
							{
								EnemyEnemyCollision(deltaTime, j, k, axis);
							}

						}
						
					}

	#ifndef DEBUG_CONFIGUREMOVEMENTSTATUS_CPP_
					if (Intersect(enemy.at(j)->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
						, enemy.at(j)->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
					{
						isEnemyDamaged[j] = IsMeDamaged();
						JudgeActorsCollision(deltaTime, enemy.at(j), fri, j, axis);
					}
	#endif
				}
			}
		}

		// ダメージを与えるための処理
		// NOTE:他の処理と切り離すことで、1フレーム内でダメージが足し算される事を防ぐ
		for (int i = 0; i < ENEMIES; i++)
		{
			if (PECorride.at(i))
			{
				wasPlayerEnemyCorrided.at(i) = true;
			}
			if (isEnemyDamaged[i])
			{
				enemy.at(i)->TakeDamage(100);
			}
		}
		if (isPlayerDamaged) { 
			player->TakeDamage(20); 
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

	void ConfigureMovementStatus::EnemyEnemyCollision(float deltaTime, int ID1, int ID2, Dim2 axis)
	{	// enemy同士のコリジョン処理

		Vector2 pos_1 = enemy.at(ID1)->GetRigidbody()->GetReplacePosition();
		Vector2 spd_1 = enemy.at(ID1)->GetRigidbody()->GetSpeed();
		Vector2 pos_2 = enemy.at(ID2)->GetRigidbody()->GetReplacePosition();
		Vector2 spd_2 = enemy.at(ID2)->GetRigidbody()->GetSpeed();

		switch (axis)
		{// 軸ごとに判定
		case Dim2::x:
			pos_1.x -= spd_1.x * deltaTime;
			pos_2.x -= spd_2.x * deltaTime;
		case Dim2::y:
			pos_1.y -= spd_1.y * deltaTime;
			pos_2.y -= spd_2.y * deltaTime;
		}

		enemy.at(ID1)->GetRigidbody()->SetReplacePosition(pos_1);
		enemy.at(ID2)->GetRigidbody()->SetReplacePosition(pos_2);

	}

	void ConfigureMovementStatus::PlayerEnemyCollision(float deltaTime, int ID, Dim2 axis)
	{
		// @todo めりこみ防止
		Vector2 p_pos = player->GetRigidbody()->GetReplacePosition();
		Vector2 p_spd = player->GetRigidbody()->GetSpeed();
		Vector2 e_pos = enemy.at(ID)->GetRigidbody()->GetReplacePosition();
		Vector2 e_spd = enemy.at(ID)->GetRigidbody()->GetSpeed();
		switch (axis)
		{
		case Dim2::x:
			// positionまきもどし
			p_pos.x -= p_spd.x * deltaTime;
			e_pos.x -= e_spd.x * deltaTime;
			// playerとenemyのx方向のスピードを入れ替え
			player->GetRigidbody()->SetSpeed(Vector2{ e_spd.x, p_spd.y});
			enemy.at(ID)->GetRigidbody()->SetSpeed(Vector2{ p_spd.x, e_spd.y });
			break;
		case Dim2::y:
			// positionまきもどし
			p_pos.y -= p_spd.y * deltaTime;
			e_pos.y -= e_spd.y * deltaTime;
			// playerとenemyのy方向のスピードを入れ替え
			player->GetRigidbody()->SetSpeed(Vector2{ p_spd.x ,e_spd.y });
			enemy.at(ID)->GetRigidbody()->SetSpeed(Vector2{ e_spd.x, p_spd.y });
			break;
		}
		// position代入
		player->GetRigidbody()->SetReplacePosition(p_pos);
		enemy.at(ID)->GetRigidbody()->SetReplacePosition(e_pos);
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
		else if ((meSpeed.x == 0.0f) && (meSpeed.y == 0.0f) && ((youSpeed.x != 0.0f) || (youSpeed.y!=0.0f)) )
		{// 衝突時meの速度が０（動いていない）かつ相手の速度が０でなければダメージ受ける
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