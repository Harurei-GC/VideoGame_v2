#include "Battle.h"
#include "../actors/Player.h"
#include "../actors/Friend.h"
#include "../actors/Mob.h"
#include "../actors/Enemy.h"
#include "../actors/Object.h"
#include "../actors/Goal.h"
#include "../actors/Sprite.h"
#include "../components/SpriteComponent.h"
#include "../Random.h"
#include <iostream>


Battle::Battle(Game* game)
	:Scene(game)
	,timeLimit(60.0f)
{
	configMoveStatus = new ConfigureMovementStatus(this);

	mPlayer = new Player(this);
	mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));

	// NOTE:Enemyが完成するまでインスタンス作成しない
	// ConfigureMovementStatus.cppやBattle.hでもコメントアウトしている
	//mFriend = new Friend(this);
	//mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));

	mMob = new Mob(this);
	mMob->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));

	// NOTE:ぬるぽ防止のためここでキーが-1のEnemyを追加
	mEnemy.insert(std::make_pair(-1, new Enemy(this, Vector2(-100.0f, -100.0f))));

	for (int i = 0; i < ENEMIES; i++)
	{
		// 部屋番号ランダム選択
		int rx = Random::Sampling(0, dangeon.GetAreaNumX()-1);
		int ry = Random::Sampling(0, dangeon.GetAreaNumY()-1);
		if (rx == 0 && dangeon.GetAreaNumX() != 1) { rx = 1; }
		else if (ry == 0) { ry = 1; }
		// 部屋左上座標取得
		Vector2Int position = dangeon.GetRoomBoxPosition(rx, ry);
		// 部屋の範囲内で座標決定
		position.x += Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).x - 1);
		position.y += Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).y - 1);
		// enemyの生成
		mEnemy.insert(std::make_pair(i,new Enemy(this, Vector2(CHARACHIP_EDGE * (position.x), CHARACHIP_EDGE * (position.y)))));
		// TODO:ゴールと被っていたら回避する処理もほしい
	}

	for (int i = 0; i < W_BOXES; i++)
	{
		for (int j = 0; j < H_BOXES; j++)
		{
			// 座標(i,j)が地形に被っていなければ
			if (!(dangeon.IsInRooms(i, j)) && !(dangeon.IsInCorridor(i, j)))
			{
				objPosition.push_back(Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
				new Object(this, Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
			}
		}
	}

	mGoal = new Goal(this);
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
				std::cout << "ゴールとエネミーが被りました" << std::endl;
				goalenemy = true;
			}
		}
	} while (goalenemy);
	mGoal->SetPosition(Vector2(CHARACHIP_EDGE * (float)goalPosition.x, CHARACHIP_EDGE * (float)goalPosition.y));


	timerBackground = new Sprite(this);
	timerBackground->SetPosition(Vector2((WIDTH - 80), 60));

}

Battle::~Battle()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

}

void Battle::Start()
{
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Start();
	}
	mUpdatingActors = false;

	configMoveStatus->Start();
}


void Battle::ProcessInput()
{
	// イベント情報event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// keyState:キーボード入力の状態を返す
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		// Escキー押すとゲームやめる
		mIsRunning = false;
	}

	// Rキー押すとキャラクターの位置リセット
	if (keyState[SDL_SCANCODE_R])
	{
		mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));
		mMob->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));
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

void Battle::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mGame->mTicksCount + 16));

	// SDLが初期化されてから今回までに経過した時間-前回までに経過した時間
	float deltaTime = (SDL_GetTicks() - mGame->mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mGame->mTicksCount = SDL_GetTicks();
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
	}
	mUpdatingActors = false;

	configMoveStatus->Update(deltaTime);
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
		else if (mEnemy.at(i)->GetState() == Actor::State::Dead)
		{
			delete mEnemy.at(i);
			configMoveStatus->EraseEnemy(i);
			mEnemy.erase(mEnemy.find(i));
		}
	}

	if (mPlayer->GetState() == Actor::State::Dead)
	{
		delete mPlayer;
	}

	// enemyが残っていればゴール判定はされなくなる
	if (mEnemy.size() > 1) { return; }

	if (GoalIntersect(*mGoal, *mMob))
	{
		mIsRunning = false;
		mGame->SetGameClear(true);
	}
}

void Battle::GenerateOutput()
{	
	// 描画操作で使う色を設定する
	SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mGame->gameRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mGame->gameRenderer);
	}


	// 残り時間表示
	RenderText(FONT_BBBOcelot, BLUE
		, std::to_string(static_cast<int>(timeLimit) + 1).c_str()
		, static_cast<int>(WIDTH - 100), 50);

	// 残りの敵の数表示
	RenderText(FONT_BBBOcelot, RED, std::to_string(mEnemy.size() - 1).c_str(), 30, 50);

	// 画面に描画
	SDL_RenderPresent(mGame->gameRenderer);
}

// 制限時間を超えたときの処理
bool Battle::IsTimeOut(float deltaTime)
{
	timeLimit -= deltaTime;
	if (timeLimit <= 0.0f) { return true; }
	return false;
}

void Battle::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Battle::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Battle::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Battle::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}



void Battle::AddObject(Object* object)
{
	mObject.emplace_back(object);
}

void Battle::RemoveObject(Object* object)
{
	auto iter = std::find(mObject.begin(),
	mObject.end(), object);
	if (iter != mObject.end())
	{
		mObject.erase(iter);
	}
}