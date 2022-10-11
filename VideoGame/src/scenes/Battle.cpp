#include "scenes/Battle.h"
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

#define TEST_VISIT // Visitor���������������ǂ���
#ifdef TEST_VISIT
#include "visitors/VisitorGetPositions.h"
#endif


namespace scenes
{
	Battle::Battle(game::Game* game)
		:scenes::Scene(game)
		,timeLimit(60.0f)
	{
		// @hack �R���X�g���N�^����剻���Ă���B
		configMoveStatus = new managers::ConfigureMovementStatus(this);

		mPlayer = new ch::Player(this);
		mPlayer->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 2.0f));

		// NOTE:Enemy����������܂ŃC���X�^���X�쐬���Ȃ�
		// ConfigureMovementStatus.cpp��Battle.h�ł��R�����g�A�E�g���Ă���
		//mFriend = new Friend(this);
		//mFriend->SetPosition(Vector2(CHARACHIP_EDGE * 2.0f, CHARACHIP_EDGE * 2.0f));

		mMBox = new ch::MBox(this);
		mMBox->SetPosition(Vector2(CHARACHIP_EDGE * 3.0f, CHARACHIP_EDGE * 3.0f));

		// NOTE:�ʂ�ۖh�~�̂��߂����ŃL�[��-1��Enemy��ǉ�
		mEnemy.insert(std::make_pair(-1, new ch::Enemy(this, Vector2(-100.0f, -100.0f))));

		for (int i = 0; i < ENEMIES; i++)
		{
			// �����ԍ������_���I��
			int rx = math::Random::Sampling(0, dangeon.GetAreaNumX()-1);
			int ry = math::Random::Sampling(0, dangeon.GetAreaNumY()-1);
			if (rx == 0 && dangeon.GetAreaNumX() != 1) { rx = 1; }
			else if (ry == 0) { ry = 1; }
			// ����������W�擾
			Vector2Int position = dangeon.GetRoomBoxPosition(rx, ry);
			// �����͈͓̔��ō��W����
			position.x += math::Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).x - 1);
			position.y += math::Random::Sampling(1, dangeon.GetRoomBoxes(rx, ry).y - 1);
			// enemy�̐���
			mEnemy.insert(std::make_pair(i,new ch::Enemy(this, Vector2(CHARACHIP_EDGE * (position.x), CHARACHIP_EDGE * (position.y)))));
			// TODO:�S�[���Ɣ���Ă����������鏈�����ق���
		}

		for (int i = 0; i < W_BOXES; i++)
		{
			for (int j = 0; j < H_BOXES; j++)
			{
				// ���W(i,j)���n�`�ɔ���Ă��Ȃ����
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
					std::cout << "�S�[���ƃG�l�~�[�����܂���" << std::endl;
					goalenemy = true;
				}
			}
		} while (goalenemy);
		mGoal->SetPosition(Vector2(CHARACHIP_EDGE * (float)goalPosition.x, CHARACHIP_EDGE * (float)goalPosition.y));


		timerBackground = new bg::Sprite(this);
		timerBackground->SetPosition(Vector2((WIDTH - 80), 60));


	#ifdef TEST_VISIT
		vstGetPos = new visitors::VisitorGetPositions(this);

	#endif
	}

	Battle::~Battle()
	{

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

	void Battle::UpdateGame()
	{
		// deltaTime�̌v�Z
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mGame->mTicksCount + 16));
		// SDL������������Ă��獡��܂łɌo�߂�������-�O��܂łɌo�߂�������
		float deltaTime = (SDL_GetTicks() - mGame->mTicksCount) / 1000.0f;

		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		mGame->mTicksCount = SDL_GetTicks();

		// �������Ԃ𒴂����Ȃ�
		if (IsTimeOut(deltaTime))
		{
			mIsRunning = false;
			mGame->SetGameOver(true);
		}

		// �����ɁAActor������Actor�ƐڐG���Ă��Ȃ����Ƃ��m�F����@�\�����āA
		// �ڐG���Ă����Rigidbody��Update���Ȃ��悤�ɂ���
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
			for (auto visitor : mVisitors)
			{
				// @hack �X�V�̃^�C�~���O�v����
				// �r�W�^�[�X�V
				actor->AcceptVisitor(visitor);
			}
		}
		mUpdatingActors = false;

		configMoveStatus->Update(deltaTime);
		// @todo ����configMoveStatus��Update���ŏ���������
		configMoveStatus->SetActorsPosition(); 


		// �ۗ�����Actor��mActors�ֈړ�
		for (auto pending : mPendingActors)
		{
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Dead��Ԃ�Enemy��delete
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

		// enemy���c���Ă���΃S�[������͂���Ȃ��Ȃ�
		if (mEnemy.size() > 1) { return; }

		if (GoalIntersect(*mGoal, *mMBox))
		{
			mIsRunning = false;
			mGame->SetGameClear(true);
		}
	}

	void Battle::GenerateOutput()
	{	
		// �`�摀��Ŏg���F��ݒ肷��
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);

		for (auto sprite : mSprites)
		{
			sprite->Draw(mGame->gameRenderer);
		}


		// �c�莞�ԕ\��
		RenderText(FONT_BBBOcelot, BLUE
			, std::to_string(static_cast<int>(timeLimit) + 1).c_str()
			, static_cast<int>(WIDTH - 100), 50);

		// �c��̓G�̐��\��
		RenderText(FONT_BBBOcelot, RED, std::to_string(mEnemy.size() - 1).c_str(), 30, 50);

		// ��ʂɕ`��
		SDL_RenderPresent(mGame->gameRenderer);
	}

	// �������Ԃ𒴂����Ƃ��̏���
	bool Battle::IsTimeOut(float deltaTime)
	{
		timeLimit -= deltaTime;
		if (timeLimit <= 0.0f) { return true; }
		return false;
	}

	void Battle::AddBlockTree(bg::BlockTree* block)
	{
		mBlkTree.emplace_back(block);
	}

	void Battle::RemoveBlockTree(bg::BlockTree* block)
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