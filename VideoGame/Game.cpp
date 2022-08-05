#include "Game.h"
#include "SDL_image.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include <iostream>
#include "Player.h"
#include "Mob.h"
#include "Object.h"
#include "Goal.h"
#include "SDL_ttf.h"
#include "MakeDangeon.h"
#include "Random.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsStart(true)
,mIsRunning(true)
,mIsCleared(false)
,mIsOver(false)
,mUpdatingActors(false)
,timeLimit(40.0f)
{
	// �擪�v�f���
	objPosition = { Vector2(-1.0f, -1.0f) };

	mColorTimer = { 30, 30, 240, 255 };
	mColorStr = { 0,0,0,255 };
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
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
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


void Game::LoadData()
{
	// Open a font & set the font size
	mFontTimer = TTF_OpenFont("font/bbbixxxel/04_Brischke/BBBOcelot-Regular.otf", 24);
	if (!mFontTimer)
	{
		std::cout << "Failed to get font for timer" << std::endl;
	}

	// Open a font & set the font size
	mFontStr = TTF_OpenFont("font/bbbixxxel/04_Brischke/BBBOcelot-Regular.otf", 24);
	if (!mFontStr)
	{
		std::cout << "Failed to get font for strings" << std::endl;
	}

	// Player�쐬
	mPlayer = new Player(this);
	mPlayer->SetPosition(Vector2(CHARACHIP_EDGE*3.0f, CHARACHIP_EDGE*2.0f));

	// Mob�쐬
	mMob = new Mob(this);
	mMob->SetPosition(Vector2(CHARACHIP_EDGE*3.0f, CHARACHIP_EDGE*3.0f));

	// ��Q��Object�쐬
	dangeon = new MakeDangeon();

	// ��ɉ�ʂ𖄂ߐs�����āA�����̕�������delete����
	for (int i = 0; i < W_BOXES; i++)
	{
		for (int j = 0; j < H_BOXES; j++)
		{
			// ���W(i,j)���n�`�ɔ���Ă��Ȃ����
			if (!(dangeon->IsInRooms(i,j)) && !(dangeon->IsInCorridor(i,j)))
			{
				objPosition.push_back(Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
				new Object(this, Vector2(CHARACHIP_EDGE * (float)i, CHARACHIP_EDGE * (float)j));
			}
		}
	}

	// Goal�쐬
	mGoal = new Goal(this);
	Vector2Int goalPosition = mGoal->RandomPosition(dangeon);
	mGoal->SetPosition(Vector2(CHARACHIP_EDGE * (float)goalPosition.x, CHARACHIP_EDGE * (float)goalPosition.y));
}


void Game::RunLoop() 
{
	// mIsRunning��true�ł�����胋�[�v��������
	while (mIsStart)
	{
		GameStart();
	}
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		while (mIsCleared)
		{
			GameClear();
			mIsRunning = false;
		}
		while (mIsOver)
		{
			GameOver();
			mIsRunning = false;
		}
	}
}


void Game::ProcessInput()
{
	// �C�x���g���event
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

	// keyState:�L�[�{�[�h���͂̏�Ԃ�Ԃ�
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		// Esc�L�[�����ƃQ�[����߂�
		mIsRunning = false;
	}

	// R�L�[�����ƃL�����N�^�[�̈ʒu���Z�b�g
	if (keyState[SDL_SCANCODE_R])
	{
		mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));
		mMob->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}


void Game::UpdateGame()
{
	// deltaTime�v�Z
	// �Ō�̃t���[������16ms�o�߂���܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// SDL������������Ă��獡��܂łɌo�߂�������-�O��܂łɌo�߂�������
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Timer�̍X�V
	// �������Ԑ؂�ɂȂ�����Q�[���I��
	if (isTimeOut(deltaTime))
	{
		mIsOver = true;
	}

	// Actor�̍X�V
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// �ۗ�����Actor��mActors�ֈړ�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Dead��Ԃ�Actor���ꎞ�z��ֈړ�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	// Dead Actor�̍폜
	for (auto dead : deadActors)
	{
		delete dead;
	}

	if (GoalIntersect(*mGoal, *mMob)) {
		
		mIsCleared = true; 
	}
}


void Game::GenerateOutput()
{
	// �`�摀��Ŏg���F��ݒ肷��
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// �S�ẴX�v���C�g�R���|�[�l���g��`��
	//WARNING:�������g�p�ʂ������Ă���
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	// �c�莞�ԕ\��
	// WARNING:�������g�p�ʂ������Ă���
	// GameStart(),GameOver(),GameClear()�����l�̂��ߏC�����K�v
	mSurfaceTimer = TTF_RenderUTF8_Blended(mFontTimer, 
		std::to_string(static_cast<int>(timeLimit)+1).c_str(), mColorTimer);
	mTextureTimer = SDL_CreateTextureFromSurface(mRenderer, mSurfaceTimer);
	int iw, ih;
	SDL_QueryTexture(mTextureTimer, NULL, NULL, &iw, &ih);

	txtRectTimer = SDL_Rect{ 0,0,iw,ih };
	pasteRectTimer = SDL_Rect{ static_cast<int>(WIDTH-100),50,iw,ih};

	SDL_RenderCopy(mRenderer, mTextureTimer, &txtRectTimer, &pasteRectTimer);
	
	// ��ʂɕ`��
	SDL_RenderPresent(mRenderer);

}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_FreeSurface(mSurfaceTimer);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_CloseFont(mFontTimer);
	TTF_CloseFont(mFontStr);
	TTF_Quit();
	SDL_Quit();
}


void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}


void Game::AddObject(Object* object)
{
	mObject.emplace_back(object);
}


void Game::RemoveObject(Object* object)
{
	auto iter = std::find(mObject.begin(),
		mObject.end(), object);
	if (iter != mObject.end())
	{
		mObject.erase(iter);
	}
}


void Game::AddActor(Actor* actor)
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


void Game::AddSprite(SpriteComponent* sprite)
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


void Game::RemoveActor(Actor* actor)
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


void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}


SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* img = IMG_Load(filename.c_str());
		if (!img)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}
		tex = SDL_CreateTextureFromSurface(mRenderer, img);
		SDL_FreeSurface(img);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
			return nullptr;
		}

		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

bool Game::isTimeOut(float deltaTime)
{
	timeLimit -= deltaTime;
	if (timeLimit <= 0.0f) { return true; }
	return false;
}