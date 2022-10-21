#include "scenes/ScnKeyConfig.h"
#include "game/Game.h"
#include <iostream>

namespace scenes
{
	ScnKeyConfig::ScnKeyConfig(game::Game* game)
		:Scene(game)
		,mKeyUpdating(false)
		,mKTypeCursor(data::KeyType::UP)
		,keyLockTime(0.0f)
		,wasPushedEtr(false)
		,wasPushedQ(false)
		,wasPushedEsc(false)
		,mKSelecting(nullptr)
		,wasSelectedCmd(SDL_SCANCODE_UNKNOWN)
	{
		mKeyData = game->GetKeyData();
		ReadTextFile("assets/KeyConfig.txt");
	}

	ScnKeyConfig::~ScnKeyConfig()
	{

	}

	void ScnKeyConfig::ProcessInput()
	{
		Scene::ProcessInput();

		if (!mKeyUpdating)
		{
			const uint8_t* keyState = SDL_GetKeyboardState(NULL);
			if (keyState[SDL_SCANCODE_ESCAPE])
			{
				mIsRunning = false;
				mGame->SetQuitGame(true);
			}
			if (keyState[SDL_SCANCODE_Q])
			{
				mIsRunning = false;
			}

		}
	}


	void ScnKeyConfig::UpdateGame()
	{
		Scene::UpdateGame();

		const uint8_t* keyState = SDL_GetKeyboardState(NULL);

		if (keyState[SDL_SCANCODE_RETURN])
		{
			SwitchKeyUpdate();
		}
		else
		{// ���̃t���[���ŃG���^�[�L�[�������Ȃ������ꍇ
			wasPushedEtr = false;
		}

		if (mKeyUpdating)// �L�[�̃A�b�v�f�[�g���̏����i�r���I�j
		{
			KeyUpdating(keyState);
		}
		else// �A�b�v�f�[�g���Ă��Ȃ��Ƃ�
		{
			NotKeyUpdating(keyState);
		}
	}

	void ScnKeyConfig::GenerateOutput()
	{
		// @todo �f�o�b�O���[�h�i�J�[�l���j�Ɣ�r���ċ������ꏏ���m�F
		// @todo �I�𒆂̂��̂ɐF��t����
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);

		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100);				// Q�L�[�ł�߂�
		RenderText(FONT_PixelMplus, BLACK, "", 100, 100 + texH);			//
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 2);	// Up
		RenderText(FONT_BBBOcelot_Regular, BLUE,
			SDL_GetKeyName(mKeyData->GetUpKey().Getter()), 350, 100 + texH * 2);// �ݒ肵���L�[
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 3);	// Down
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 4);	// Right
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 5);	// Left
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 6);	// Reset

		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}

	

	/* Update Functions */

	void ScnKeyConfig::SwitchKeyUpdate()
	{// �G���^�[�ŁA�L�[�̃A�b�v�f�[�gON|OFF
		if (!wasPushedEtr)
		{// �O��̃t���[���ŃG���^�[�L�[�������Ă��Ȃ�
		 // �������n�߂̏ꍇ�A�������s
			wasPushedEtr = true;	// ����ȍ~�̃t���[���ŁA�A������Enter�L�[���͂��ł��Ȃ��悤�ɂ���

			mKeyUpdating = !mKeyUpdating;

			std::cout << "Updating: " << mKeyUpdating << std::endl;

			if (mKeyUpdating)// �L�[�̃A�b�v�f�[�g���Ɍ�����s
			{
				// KeyData���̃R�}���h��I�����o�^
				mKSelecting = RegistKType();
			}
		}
	}

	SG_Scancode* ScnKeyConfig::RegistKType()
	{
		// ���݂�mKeyType�ɑΉ�����KeyData::mKey��Getter��Ԃ�
		switch (mKTypeCursor)
		{
		case data::KeyType::UP:
			return mKeyData->GetPtrUpKey();
		case data::KeyType::DOWN:
			return mKeyData->GetPtrDownKey();
		case data::KeyType::RIGHT:
			return mKeyData->GetPtrRightKey();
		case data::KeyType::LEFT:
			return mKeyData->GetPtrLeftKey();
		case data::KeyType::RESET:
			return mKeyData->GetPtrResetKey();
		default:
			return nullptr;
		}
	}

	void ScnKeyConfig::KeyUpdating(const uint8_t* keyState)
	{
		for (int i = static_cast<int>(SDL_SCANCODE_A); i <= static_cast<int>(SDL_SCANCODE_UP); i++)// ���C���Ŏg���ł��낤�L�[�܂ŁB�ڍׂ�SDL_Scancode�Q��
		{
			SDL_Scancode code = static_cast<SDL_Scancode>(i);

			if (keyState[code])// i�Ԗڂ̃L�[��������Ă����
			{
				// �\�񂳂�Ă���L�[�̏ꍇ�A�X�V�ł��Ȃ�
				if (code == SDL_SCANCODE_RETURN)
				{
					if (wasPushedEtr) { break; }
					CannotUpdateKey(wasPushedEtr);
					break;
				}
				else if (code == SDL_SCANCODE_Q)
				{
					if (wasPushedQ) { break; }
					CannotUpdateKey(wasPushedQ);
					break;
				}
				else if (code == SDL_SCANCODE_ESCAPE)
				{
					if (wasPushedEsc) { break; }
					CannotUpdateKey(wasPushedEsc);
					break;
				}

				// �L�[�X�V
				IsKeyAlreadyUsed(code);					// �L�[�̔�肪�Ȃ����A����ꍇ�̓L�[�X�V
				mKSelecting->Setter(code);				// �V�����L�[��KeyData�ɓo�^
				wasSelectedCmd = mKSelecting->Getter();	// ���̃t���[���ŉ������L�[���L���i���t���[���ȍ~�̘A�����͖h�~�j
				mKSelecting = nullptr;					// �|�C���^���
				mKeyUpdating = false;					// �A�b�v�f�[�g����
#ifdef DEBUG_SCNKEYCONFIG_H_
				// @todo SDL_GetKeyName�̋����m�F�@�{���ɕ����񂪕Ԃ��Ă���̂��H
				std::cout << SDL_GetKeyName(wasSelectedCmd) << static_cast<int>(wasSelectedCmd) << " key was registered" << std::endl;
				PrintRgsteredKey();						// �����ő��̃L�[�̌��ݒl���o��
#endif
				break;
			}
			else // i�Ԗڂ�������Ă��Ȃ��Ƃ�
			{
				if (code == SDL_SCANCODE_RETURN) { wasPushedEtr = false; }
				else if (code == SDL_SCANCODE_Q) { wasPushedQ = false; }
				else if (code == SDL_SCANCODE_ESCAPE) { wasPushedEsc = false; }
			}
		}
	}

	void ScnKeyConfig::IsKeyAlreadyUsed(SDL_Scancode& code)
	{
		SDL_Scancode UpKey = mKeyData->GetUpKey().Getter();
		SDL_Scancode DownKey = mKeyData->GetDownKey().Getter();
		SDL_Scancode RightKey = mKeyData->GetRightKey().Getter();
		SDL_Scancode LeftKey = mKeyData->GetLeftKey().Getter();
		SDL_Scancode ResetKey = mKeyData->GetResetKey().Getter();

		// �����o�^����L�[�����ɑ��̃R�}���h�Ɏg�p����Ă�����
		// ���̃R�}���h�̃L�[��selecting�L�[��o�^
		if (code == UpKey) { 
			mKeyData->GetPtrUpKey()->Setter(mKSelecting->Getter());
		}
		else if (code == DownKey)
		{
			mKeyData->GetPtrDownKey()->Setter(mKSelecting->Getter());
		}
		else if (code == RightKey)
		{
			mKeyData->GetPtrRightKey()->Setter(mKSelecting->Getter());
		}
		else if (code == LeftKey)
		{
			mKeyData->GetPtrLeftKey()->Setter(mKSelecting->Getter());
		}
		else if (code == ResetKey)
		{
			mKeyData->GetPtrResetKey()->Setter(mKSelecting->Getter());
		}
	}

	void ScnKeyConfig::CannotUpdateKey(bool& wasPushed)
	{
		wasPushed = true;
		// @todo �����Ɂu�X�V�ł��܂���v�̏���
		// ���������A�b�v�f�[�g���ƂȂ�
		std::cout << "cannot update for that key" << std::endl;
	}

	void ScnKeyConfig::NotKeyUpdating(const uint8_t* keyState)
	{
		// �O�t���[���ŉ����ꂽ�L�[���A���̃t���[���ŉ�����Ă��Ȃ����
		if (!keyState[wasSelectedCmd])
		{
			wasSelectedCmd = SDL_SCANCODE_UNKNOWN;
		}

		SDL_Scancode UpKey = mKeyData->GetUpKey().Getter();
		SDL_Scancode DownKey = mKeyData->GetDownKey().Getter();
		SDL_Scancode RightKey = mKeyData->GetRightKey().Getter();
		SDL_Scancode LeftKey = mKeyData->GetLeftKey().Getter();
		SDL_Scancode ResetKey = mKeyData->GetResetKey().Getter();

		// KeyData�œo�^����Ă���L�[�������ꂽ��A
		// ���O�t���[������A���ŉ�����Ă��Ȃ���΁A
		// KeyTypeSelect��ԂɈڍs
		if (keyState[UpKey] && (UpKey != wasSelectedCmd))
		{
			RenewCursor(&UpKey, data::KeyType::UP, "Up");
		}
		else if (keyState[DownKey] && (DownKey != wasSelectedCmd))
		{
			RenewCursor(&DownKey, data::KeyType::DOWN, "Down");
		}
		else if (keyState[RightKey] && (RightKey != wasSelectedCmd))
		{
			RenewCursor(&RightKey, data::KeyType::RIGHT, "Right");
		}
		else if (keyState[LeftKey] && (LeftKey != wasSelectedCmd))
		{
			RenewCursor(&LeftKey, data::KeyType::LEFT, "Left");
		}
		else if (keyState[ResetKey] && (ResetKey != wasSelectedCmd))
		{
			RenewCursor(&ResetKey, data::KeyType::RESET, "Reset");
		}
	}

	void ScnKeyConfig::RenewCursor(SDL_Scancode* key, data::KeyType type, std::string cmdName)
	{
		std::cout << cmdName << "Key is now selected" << std::endl;
		mKTypeCursor = type;
		wasSelectedCmd = *key;

	}

	/* End of Update Functinos */


#ifdef DEBUG_SCNKEYCONFIG_H_
	void ScnKeyConfig::PrintRgsteredKey()
	{
		std::cout << "Now Key Config Settings: " << std::endl;
		std::cout << "Up Key: " << SDL_GetKeyName(mKeyData->GetUpKey().Getter()) << std::endl;
		std::cout << "Down Key: " << SDL_GetKeyName(mKeyData->GetDownKey().Getter()) << std::endl;
		std::cout << "Right Key: " << SDL_GetKeyName(mKeyData->GetRightKey().Getter()) << std::endl;
		std::cout << "Left Key: " << SDL_GetKeyName(mKeyData->GetLeftKey().Getter()) << std::endl;
		std::cout << "Reset Key: " << SDL_GetKeyName(mKeyData->GetResetKey().Getter()) << std::endl;
		std::cout << std::endl;
	}
#endif
}
