// GameManager�̂悤�Ȗ���
// Scene�N���X���쐬���Ǘ�����i�|�C���^�ł͂Ȃ����ʂ̐錾�j
// �Q�[���̋L�q�͍s��Ȃ�

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
	// �擪�v�f���
	//objPosition = { Vector2(-1.0f, -1.0f) };

	//mColor[BLACK] = {0,0,0,255};
	//mColor[BLUE] = {30, 30, 240, 255};
}

bool Game::Initialize() 
{
	// SDL���C�u����������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// �E�B���h�E�쐬(�^�C�g��)
	mWindow = SDL_CreateWindow("Video Game", 100, 100, WIDTH, HEIGHT, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// 2D�����_�����O�R���e�L�X�g�쐬
	gameRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!gameRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// �摜�`���ǂݍ��߂�悤�ɂ���
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	// TTF���C�u����������
	if (TTF_Init() == -1)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
	}


	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}


// �e�V�[���ɕK�v�Ȃ��̂������Ă���
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

	//// �e�L�X�g�t�@�C���ǂݍ���
	//// �Ȃ����R�}���h���C���ɕ\�������
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

	//// NOTE:�ʂ�ۖh�~�̂��߂����ŃL�[��-1��Enemy��ǉ�
	//new Enemy(this, Vector2(-100.0f, -100.0f), -1);
	//mEnemy.at(-1)->SetPosition(mEnemy.at(-1)->GetInitialPosition());
	//for (int i = 0; i < ENEMIES; i++)
	//{
	//	// TODO:position�͂��̂��������_������������
	//	new Enemy(this, Vector2(CHARACHIP_EDGE * 5.0f, CHARACHIP_EDGE * 2.0f), i);
	//	mEnemy.at(i)->SetPosition(mEnemy.at(i)->GetInitialPosition());
	//}

	//dangeon = new MakeDangeon();

	// ��ɉ�ʂ𖄂ߐs�����āA�����̕�������delete����
	//for (int i = 0; i < W_BOXES; i++)
	//{
	//	for (int j = 0; j < H_BOXES; j++)
	//	{
	//		// ���W(i,j)���n�`�ɔ���Ă��Ȃ����
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

	// TODO:Scene�̒ǉ�
	start = new Start(this);
	battle = new Battle(this);
	gameClear = new GameClear(this);
	gameOver = new GameOver(this);

	// Start()�����s�������Ƃ��͂����ɓ���� 
	

	//mUpdatingActors = false;
}


void Game::RunLoop() 
{
	//// TODO:������Scene����Q�[�������I���̃t���O���󂯂���悤�ɂ���
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
	for (int i = 0; i < FONT; i++) // i��mFont�̗v�f��
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
//	// �C�x���g���event
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
//	// keyState:�L�[�{�[�h���͂̏�Ԃ�Ԃ�
//	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
//	if (keyState[SDL_SCANCODE_ESCAPE])
//	{
//		// Esc�L�[�����ƃQ�[����߂�
//		mIsRunning = false;
//	}
//
//	// R�L�[�����ƃL�����N�^�[�̈ʒu���Z�b�g
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
//	//// deltaTime�v�Z
//	//// �Ō�̃t���[������16ms�o�߂���܂ő҂�
//	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
//
//	//// SDL������������Ă��獡��܂łɌo�߂�������-�O��܂łɌo�߂�������
//	//float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
//	//if (deltaTime > 0.05f)
//	//{
//	//	deltaTime = 0.05f;
//	//}
//	//mTicksCount = SDL_GetTicks();
//
//	// Timer�̍X�V
//	// �������Ԑ؂�ɂȂ�����Q�[���I��
//	//if (isTimeOut(deltaTime))
//	//{
//	//	mIsOver = true;
//	//}
//	
//	// �����ɁAActor������Actor�ƐڐG���Ă��Ȃ����Ƃ��m�F����@�\�����āA
//	// �ڐG���Ă����Rigidbody��Update���Ȃ��悤�ɂ���
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
//	// �ۗ�����Actor��mActors�ֈړ�
//	for (auto pending : mPendingActors)
//	{
//		mActors.emplace_back(pending);
//	}
//	mPendingActors.clear();
//
//	// Dead��Ԃ�Actor���ꎞ�z��ֈړ�
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
//	// �`�摀��Ŏg���F��ݒ肷��
//	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
//	SDL_RenderClear(mRenderer);
//
//	for (auto sprite : mSprites)
//	{
//		sprite->Draw(mRenderer);
//	}
//
//
//	// �c�莞�ԕ\��
//	RenderText(FONT_BBBOcelot, BLUE
//		, std::to_string(static_cast<int>(timeLimit) + 1).c_str()
//		, static_cast<int>(WIDTH-100),50);
//	
//	// ��ʂɕ`��
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
//// TODO:�����Ǝw���ID��Enemy��������悤�ɂ���
//// vector�̎d�l�̂܂�map�^��mEnemy�ɉ��p���Ă���̂ŁA�o�O�̉\������
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
