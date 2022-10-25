#include "scenes/ScnBattle.h"
#include "actors/characters/Player.h"
#include "actors/characters/Friend.h"
#include "actors/characters/MBox.h"
#include "actors/characters/Enemy.h"
#include "actors/background/BlockTree.h"
#include "actors/background/Goal.h"
#include "actors/background/Sprite.h"
#include "components/SpriteComponent.h"
#include "math/Random.h"
#include "managers/ConfigureMovementStatus.h"
#include <iostream>
#include "scenes/ScnGameClear.h"
#include "data/KeyData.h"

#define DEBUG_TESTING_VISIT_SCNBATTLE_CPP_ // Visitorが正しく動くかどうか
#ifdef DEBUG_TESTING_VISIT_SCNBATTLE_CPP_
#include "visitors/VisitorGetPositions.h"
#endif


namespace scenes
{
	ScnBattle::ScnBattle(game::Game* game)
		:scenes::Scene(game)
		,timeLimit(60.0f)
		,mScore(Score::C)
	{
		// @hack コンストラクタが肥大化している。
		configMoveStatus = new managers::ConfigureMovementStatus(this);

		mPlayer = new ch::Player(this);
		mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));

		// NOTE:Enemyが完成するまでインスタンス作成しない
		// ConfigureMovementStatus.cppやBattle.hでもコメントアウトしている
		//mFriend = new Friend(this);
		//mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));

		mMBox = new ch::MBox(this);
		mMBox->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));

		// NOTE:ぬるぽ防止のためここでキーが-1のEnemyを追加
		mEnemy.insert(std::make_pair(-1, new ch::Enemy(this, Vector2(-100.0f, -100.0f))));

		for (int i = 0; i < ENEMIES; i++)
		{
			// 部屋番号ランダム選択
			int rx = math::Random::Sampling(0, dangeon.GetAreaNumX()-1);
			int ry = math::Random::Sampling(0, dangeon.GetAreaNumY()-1);
			if (rx == 0 && dangeon.GetAreaNumX() != 1) { rx = 1; }
			else if (ry == 0) { ry = 1; }
			// 部屋左上座標取得
			Vector2Int position = dangeon.GetRoomBoxPosition(rx, ry);
			// 部屋の範囲内で座標決定
			position.x += math::Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).x - 1);
			position.y += math::Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).y - 1);
			// enemyの生成
			mEnemy.insert(std::make_pair(i,new ch::Enemy(this, Vector2(CHARACHIP_EDGE * (position.x), CHARACHIP_EDGE * (position.y)))));
			// TODO:ゴールと被っていたら回避する処理もほしい
		}

		for (int i = 0; i < W_BOXES; i++)
		{
			for (int j = 0; j < H_BOXES; j++)
			{
				// 座標(i,j)が地形に被っていなければ
				if (!(dangeon.IsInRooms(i, j)) && !(dangeon.IsInCorridor(i, j)))
				{
					boxPosition.push_back(Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
					new bg::BlockTree(this, Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
				}
			}
		}

		mGoal = new bg::Goal(this);
		Vector2Int goalPosition;
		bool goalenemy = false;
		do
		{
			goalPosition = mGoal->RandomPosition(&dangeon);
			goalenemy = false;
			for (int i = 0; i < ENEMIES; i++)
			{
				if (goalPosition.x == int(mEnemy.at(i)->GetInitialPosition().x) && goalPosition.y == int(mEnemy.at(i)->GetInitialPosition().y))
				{
					goalenemy = true;
				}
			}
		} while (goalenemy);
		mGoal->SetPosition(Vector2(CHARACHIP_EDGE * (float)goalPosition.x, CHARACHIP_EDGE * (float)goalPosition.y));


		timerBackground = new bg::Sprite(this);
		timerBackground->SetPosition(Vector2((WIDTH - 80), 60));


#ifdef DEBUG_TESTING_VISIT_SCNBATTLE_CPP_
		vstGetPos = new visitors::VisitorGetPositions(this);

#endif
	}

	ScnBattle::~ScnBattle()
	{

	}

	void ScnBattle::Start()
	{
		Scene::Start();
		configMoveStatus->Start();
	}


	void ScnBattle::ProcessInput()
	{
		Scene::ProcessInput();

		// keyState:キーボード入力の状態を返す
		const uint8_t* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			// Escキー押すとゲームやめる
			mIsRunning = false;
		}

		// Rキー押すとキャラクターの位置リセット
		if (keyState[mGame->GetKeyData()->GetResetKey().Getter()])
		{
			mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));
			mMBox->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));
			// mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));
			for (auto iter = mEnemy.begin(); iter != mEnemy.end(); ++iter)
			{
				iter->second->SetPosition(iter->second->GetInitialPosition());
			}
		}
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(keyState);
		}
		mUpdatingActors = false;
	}

	void ScnBattle::UpdateGame()
	{
		Scene::UpdateGame();

		// 制限時間を超えたなら
		if (IsTimeOut(deltaTime))
		{
			mIsRunning = false;
			mGame->SetGameOver(true);
		}

		// ここに、Actorが他のActorと接触していないことを確認する機能を入れて、
		// 接触していればRigidbodyをUpdateしないようにする
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
			for (auto visitor : mVisitors)
			{
				// @hack 更新のタイミング要検討
				// ビジター更新
				actor->AcceptVisitor(visitor);
			}
		}
		mUpdatingActors = false;

		configMoveStatus->Update(deltaTime);
		// @todo これconfigMoveStatusのUpdate内で処理させる
		configMoveStatus->SetActorsPosition(); 


		// 保留中のActorをmActorsへ移動
		for (auto pending : mPendingActors)
		{
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Dead状態のEnemyをdelete
		for (int i = 0; i < ENEMIES; i++)
		{
			if(mEnemy.find(i)==mEnemy.end()) 
			{
				continue;
			}
			else if (mEnemy.at(i)->GetState() == actors::Actor::State::Dead)
			{
				delete mEnemy.at(i);
				configMoveStatus->EraseEnemy(i);
				mEnemy.erase(mEnemy.find(i));
			}
		}

		if (mPlayer->GetState() == actors::Actor::State::Dead)
		{
			delete mPlayer;
		}

		// ゴールしたならば
		if (GoalIntersect(*mGoal, *mMBox))
		{
			mIsRunning = false;
			mGame->SetGameClear(true);
			mGame->gameClear->SetScore(mScore);
		}
	}

	void ScnBattle::GenerateOutput()
	{	
		// 描画操作で使う色を設定する
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);

		for (auto sprite : mSprites)
		{
			sprite->Draw(mGame->gameRenderer);
		}


		// 残り時間表示
		RenderText(FONT_BBBOcelot_Regular, BLUE
			, std::to_string(static_cast<int>(timeLimit) + 1).c_str()
			, static_cast<int>(WIDTH - 100), 40);

		// 現在のスコアひょうじ
		switch (mEnemy.size() - 1)
		{
		case 0:
			mScore = Score::A;
			RenderText(FONT_BBBOcelot_Regular, RED, "A", (WIDTH - 90), 66);
			break;
		case 1:
			mScore = Score::B;
			RenderText(FONT_BBBOcelot_Regular, BLUE, "B", (WIDTH-90),66);
			break;
		case 2:
			mScore = Score::C;
			RenderText(FONT_BBBOcelot_Regular, YELLOW, "C", (WIDTH-90), 66);
			break;
		default:
			mScore = Score::C;
			RenderText(FONT_BBBOcelot_Regular, YELLOW, "C", (WIDTH-90), 66);
			break;
		}

		// 画面に描画
		SDL_RenderPresent(mGame->gameRenderer);
	}

	// 制限時間を超えたときの処理
	bool ScnBattle::IsTimeOut(float deltaTime)
	{
		timeLimit -= deltaTime;
		if (timeLimit <= 0.0f) { return true; }
		return false;
	}

	void ScnBattle::AddBlockTree(bg::BlockTree* block)
	{
		mBlkTree.emplace_back(block);
	}

	void ScnBattle::RemoveBlockTree(bg::BlockTree* block)
	{
		auto iter = std::find(mBlkTree.begin(),
		mBlkTree.end(), block);
		if (iter != mBlkTree.end())
		{
			std::iter_swap(iter, mBlkTree.end() - 1);
			mBlkTree.pop_back();
		}

	}
}