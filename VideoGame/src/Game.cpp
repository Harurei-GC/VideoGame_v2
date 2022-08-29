// GameManagerのような役割
// Sceneクラスを作成し管理する（ポインタではない普通の宣言）
// ゲームの記述は行わない

#include "Game.h"
#include "SDL_image.h"
#include "actors/Actor.h"
#include "components/SpriteComponent.h"
#include <iostream>
#include "actors/Player.h"
#include "actors/Mob.h"
#include "actors/Object.h"
#include "actors/Goal.h"
#include "SDL_ttf.h"
#include "managers/MakeDangeon.h"
#include "Random.h"
#include "actors/Enemy.h"
#include "actors/Friend.h"
#include "actors/Sprite.h"
#include "managers/ConfigureMovementStatus.h"
#include "scenes/Start.h"
#include "scenes/Battle.h"
#include "scenes/GameClear.h"
#include "scenes/GameOver.h"

Game::Game()
:mWindow(nullptr)
//,mRenderer(nullptr)
//,mIsStart(true)
//,mIsRunning(true)
,mIsCleared(false)
,mIsOver(false)
//,mUpdatingActors(false)
,timeLimit(35.0f)
//,bufCount(0)
,quitGame(false)
{
	// 先頭要素代入
	//objPosition = { Vector2(-1.0f, -1.0f) };

	//mColor[BLACK] = {0,0,0,255};
	//mColor[BLUE] = {30, 30, 240, 255};
}

bool Game::Initialize() 
{
	// SDLライブラリ初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// ウィンドウ作成(タイトル)
	mWindow = SDL_CreateWindow("Video Game", 100, 100, WIDTH, HEIGHT, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// 2Dレンダリングコンテキスト作成
	gameRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!gameRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// 画像形式読み込めるようにする
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	// TTFライブラリ初期化
	if (TTF_Init() == -1)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
	}


	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}


// 各シーンに必要なものを持っていく
void Game::LoadData()
{
	mFont[FONT_BBBOcelot] = TTF_OpenFont("font/bbbixxxel/04_Brischke/BBBOcelot-Regular.otf", 24);
	if (!mFont[FONT_BBBOcelot])
	{
		std::cout << "Failed to get font for timer" << std::endl;
	}
	mFont[FONT_PixelMplus] = TTF_OpenFont("font/PixelMplus-20130602/PixelMplus12-Regular.ttf", 24);
	if (!mFont[FONT_PixelMplus])
	{
		std::cout << "Failed to get font for timer" << std::endl;
	}

	//// テキストファイル読み込み
	//// なぜかコマンドラインに表示される
	//if (fopen_s(&fp, "assets/Text.txt", "r") != 0)
	//{
	//	std::cout << "Failed to open a text file" << std::endl;
	//}
	//else
	//{
	//	int i = 0;
	//	while ((buf[i] = fgetc(fp)) != EOF)
	//	{
	//		putchar(buf[i]);
	//		i++;
	//	}
	//	fclose(fp);
	//}


	//mPlayer = new Player(this);
	//mPlayer->SetPosition(Vector2(CHARACHIP_EDGE*3.0f, CHARACHIP_EDGE*2.0f));

	//mFriend = new Friend(this);
	//mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));

	//mMob = new Mob(this);
	//mMob->SetPosition(Vector2(CHARACHIP_EDGE*3.0f, CHARACHIP_EDGE*3.0f));

	//// NOTE:ぬるぽ防止のためここでキーが-1のEnemyを追加
	//new Enemy(this, Vector2(-100.0f, -100.0f), -1);
	//mEnemy.at(-1)->SetPosition(mEnemy.at(-1)->GetInitialPosition());
	//for (int i = 0; i < ENEMIES; i++)
	//{
	//	// TODO:positionはそのうちランダム生成させる
	//	new Enemy(this, Vector2(CHARACHIP_EDGE * 5.0f, CHARACHIP_EDGE * 2.0f), i);
	//	mEnemy.at(i)->SetPosition(mEnemy.at(i)->GetInitialPosition());
	//}

	//dangeon = new MakeDangeon();

	// 先に画面を埋め尽くして、部屋の部分だけdeleteする
	//for (int i = 0; i < W_BOXES; i++)
	//{
	//	for (int j = 0; j < H_BOXES; j++)
	//	{
	//		// 座標(i,j)が地形に被っていなければ
	//		if (!(dangeon->IsInRooms(i,j)) && !(dangeon->IsInCorridor(i,j)))
	//		{
	//			objPosition.push_back(Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
	//			new Object(this, Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
	//		}
	//	}
	//}

	//mGoal = new Goal(this);
	//Vector2Int goalPosition = mGoal->RandomPosition(dangeon);
	//mGoal->SetPosition(Vector2(CHARACHIP_EDGE * (float)goalPosition.x, CHARACHIP_EDGE * (float)goalPosition.y));

	//configMoveStatus = new ConfigureMovementStatus(this);
	
	//timerBackground = new Sprite(this);
	//timerBackground->SetPosition(Vector2((WIDTH - 80), 60));

	//mUpdatingActors = true;

	// TODO:Sceneの追加
	start = new Start(this);
	battle = new Battle(this);
	gameClear = new GameClear(this);
	gameOver = new GameOver(this);

	// Start()を実行したいときはここに入れる 
	

	//mUpdatingActors = false;
}


void Game::RunLoop() 
{
	//// TODO:ここにSceneからゲーム強制終了のフラグを受けられるようにする
	//while (mIsStart)
	//{
	//	GameStart();
	//}
	//while (mIsRunning)
	//{
	//	ProcessInput();
	//	UpdateGame();
	//	GenerateOutput();
	//	while (mIsCleared)
	//	{
	//		GameClear();
	//		mIsRunning = false;
	//	}
	//	while (mIsOver)
	//	{
	//		GameOver();
	//		mIsRunning = false;
	//	}
	//}
	while (start->GetIsRunning())
	{
		start->RunLoop();
	}
	if (quitGame) { return; }
	while (battle->GetIsRunning())
	{
		battle->RunLoop();
	}
	if (quitGame) { return; }
	if (mIsCleared)
	{
		while (gameClear->GetIsRunning())
		{
			gameClear->RunLoop();
		}
	}
	if (quitGame) { return; }
	if (mIsOver)
	{
		while (gameOver->GetIsRunning())
		{
			gameOver->RunLoop();
		}
	}

}

void Game::Shutdown()
{
	//UnloadData();
	UnloadScene();
	IMG_Quit();
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(mWindow);
	for (int i = 0; i < FONT; i++) // iはmFontの要素数
	{
		TTF_CloseFont(mFont[i]);
	}
	TTF_Quit();
	SDL_Quit();
}


void Game::AddScene(Scene* scene)
{
	mScenes.emplace_back(scene);
}

void Game::UnloadScene()
{
	while (!mScenes.empty())
	{
		delete mScenes.back();
	}
}

//void Game::ProcessInput()
//{
//	// イベント情報event
//	SDL_Event event;
//	while (SDL_PollEvent(&event)) 
//	{
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			mIsRunning = false; 
//			break;
//		}
//	}
//
//	// keyState:キーボード入力の状態を返す
//	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
//	if (keyState[SDL_SCANCODE_ESCAPE])
//	{
//		// Escキー押すとゲームやめる
//		mIsRunning = false;
//	}
//
//	// Rキー押すとキャラクターの位置リセット
//	if (keyState[SDL_SCANCODE_R])
//	{
//		mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));
//		mMob->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));
//		mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));
//		for (int i = 0; i < ENEMIES; i++)
//		{
//			mEnemy.at(i)->SetPosition(mEnemy.at(i)->GetInitialPosition());
//		}
//	}
//
//	mUpdatingActors = true;
//	for (auto actor : mActors)
//	{
//		actor->ProcessInput(keyState);
//	}
//	mUpdatingActors = false;
//}


//void Game::UpdateGame()
//{
//	//// deltaTime計算
//	//// 最後のフレームから16ms経過するまで待つ
//	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
//
//	//// SDLが初期化されてから今回までに経過した時間-前回までに経過した時間
//	//float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
//	//if (deltaTime > 0.05f)
//	//{
//	//	deltaTime = 0.05f;
//	//}
//	//mTicksCount = SDL_GetTicks();
//
//	// Timerの更新
//	// もし時間切れになったらゲーム終了
//	//if (isTimeOut(deltaTime))
//	//{
//	//	mIsOver = true;
//	//}
//	
//	// ここに、Actorが他のActorと接触していないことを確認する機能を入れて、
//	// 接触していればRigidbodyをUpdateしないようにする
//	mUpdatingActors = true;
//	for (auto actor : mActors)
//	{
//		actor->Update(deltaTime);
//	}
//	mUpdatingActors = false;
//
//	configMoveStatus->Update(deltaTime);
//	configMoveStatus->SetActorsPosition();
//
//	// 保留中のActorをmActorsへ移動
//	for (auto pending : mPendingActors)
//	{
//		mActors.emplace_back(pending);
//	}
//	mPendingActors.clear();
//
//	// Dead状態のActorを一時配列へ移動
//	std::vector<Actor*> deadActors;
//	for (auto actor : mActors)
//	{
//		if (actor->GetState() == Actor::State::Dead)
//		{
//			deadActors.emplace_back(actor);
//		}
//	}
//	for (auto dead : deadActors)
//	{
//		delete dead;
//	}
//
//	//if (GoalIntersect(*mGoal, *mMob)) {
//	//	
//	//	mIsCleared = true; 
//	//}
//}


//void Game::GenerateOutput()
//{
//	// 描画操作で使う色を設定する
//	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
//	SDL_RenderClear(mRenderer);
//
//	for (auto sprite : mSprites)
//	{
//		sprite->Draw(mRenderer);
//	}
//
//
//	// 残り時間表示
//	RenderText(FONT_BBBOcelot, BLUE
//		, std::to_string(static_cast<int>(timeLimit) + 1).c_str()
//		, static_cast<int>(WIDTH-100),50);
//	
//	// 画面に描画
//	SDL_RenderPresent(mRenderer);
//
//}

//
//void Game::RenderText(int font, int color, const char* text, int rw,int rh)
//{
//	SDL_Surface* surf = TTF_RenderUTF8_Blended(mFont[font], text, mColor[color]);
//	SDL_Texture* txtr = SDL_CreateTextureFromSurface(mRenderer, surf);
//	SDL_QueryTexture(txtr, NULL, NULL, &iw, &ih);
//	txtRect = SDL_Rect{ 0,0,iw,ih };
//	pasteRect = SDL_Rect{ rw,rh,iw,ih };
//	SDL_RenderCopy(mRenderer, txtr, &txtRect, &pasteRect);
//	SDL_FreeSurface(surf);
//	SDL_DestroyTexture(txtr);
//}




//void Game::UnloadData()
//{
//	while (!mActors.empty())
//	{
//		delete mActors.back();
//	}
//
//	for (auto i : mTextures)
//	{
//		SDL_DestroyTexture(i.second);
//	}
//	mTextures.clear();
//}


//bool Game::isTimeOut(float deltaTime)
//{
//	timeLimit -= deltaTime;
//	if (timeLimit <= 0.0f) { return true; }
//	return false;
//}

//
//void Game::AddObject(Object* object)
//{
//	mObject.emplace_back(object);
//}
//
//
//void Game::RemoveObject(Object* object)
//{
//	auto iter = std::find(mObject.begin(),
//		mObject.end(), object);
//	if (iter != mObject.end())
//	{
//		mObject.erase(iter);
//	}
//}
//
//
//void Game::AddEnemy(int key,Enemy* enemy)
//{
//	mEnemy.emplace(key,enemy);
//}
//
//// TODO:ちゃんと指定のIDのEnemyが消えるようにする
//// vectorの仕様のままmap型のmEnemyに応用しているので、バグの可能性あり
//void Game::RemoveEnemy(int key)
//{
//	mEnemy.erase(key);
//}
//
//
//void Game::AddActor(Actor* actor)
//{
//	if (mUpdatingActors)
//	{
//		mPendingActors.emplace_back(actor);
//	}
//	else
//	{
//		mActors.emplace_back(actor);
//	}
//}
//
//
//void Game::AddSprite(SpriteComponent* sprite)
//{
//	int myDrawOrder = sprite->GetDrawOrder();
//	auto iter = mSprites.begin();
//	for (; iter != mSprites.end(); iter++)
//	{
//		if (myDrawOrder < (*iter)->GetDrawOrder())
//		{
//			break;
//		}
//	}
//	mSprites.insert(iter, sprite);
//}
//
//
//void Game::RemoveActor(Actor* actor)
//{
//	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
//	if (iter != mPendingActors.end())
//	{
//		std::iter_swap(iter, mPendingActors.end() - 1);
//		mPendingActors.pop_back();
//	}
//
//	iter = std::find(mActors.begin(), mActors.end(), actor);
//	if (iter != mActors.end())
//	{
//		std::iter_swap(iter, mActors.end() - 1);
//		mActors.pop_back();
//	}
//}
//
//
//void Game::RemoveSprite(SpriteComponent* sprite)
//{
//	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
//	mSprites.erase(iter);
//}


//SDL_Texture* Game::GetTexture(const std::string& filename)
//{
//	SDL_Texture* tex = nullptr;
//	auto iter = mTextures.find(filename);
//	if (iter != mTextures.end())
//	{
//		tex = iter->second;
//	}
//	else
//	{
//		SDL_Surface* img = IMG_Load(filename.c_str());
//		if (!img)
//		{
//			SDL_Log("Failed to load texture file %s", filename.c_str());
//			return nullptr;
//		}
//		tex = SDL_CreateTextureFromSurface(mRenderer, img);
//		SDL_FreeSurface(img);
//		if (!tex)
//		{
//			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
//			return nullptr;
//		}
//
//		mTextures.emplace(filename.c_str(), tex);
//	}
//	return tex;
//}
