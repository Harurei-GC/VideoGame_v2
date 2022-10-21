#pragma once
#include "scenes/Scene.h"
#include "data/KeyData.h"

#define DEBUG_SCNKEYCONFIG_H_

namespace data { class KeyData; }

namespace scenes
{
	class ScnKeyConfig : public Scene
	{
	public:
		ScnKeyConfig(game::Game* game);
		~ScnKeyConfig();

		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:

		data::KeyData* mKeyData;	// �L�[�z�u���L������N���X
		data::KeyType mKTypeCursor;	// ���݃J�[�\�������킹�Ă���R�}���h
		SG_Scancode* mKSelecting;	// ���ݍX�V���̃L�[
		SDL_Scancode wasSelectedCmd;// �O�t���[���őI�����ꂽ�R�}���h
		bool mKeyUpdating;	// �L�[�{�^���̍X�V����
		float keyLockTime;	// �L�[���͂��󂯕t���Ȃ�����
		bool wasPushedEtr;	// ���O�̃t���[����Enter�L�[��������Ă�����
		bool wasPushedQ;
		bool wasPushedEsc;

		/* Update Functinos */
		void SwitchKeyUpdate();
		SG_Scancode* RegistKType();
		void IsKeyAlreadyUsed(SDL_Scancode& code);
		void CannotUpdateKey(bool& wasPushed);
		void KeyUpdating(const uint8_t* keyState);
		void NotKeyUpdating(const uint8_t* keyState);
		void RenewCursor(SDL_Scancode* key, data::KeyType type, std::string cmdName);
		/* End of Update Functions */

#ifdef DEBUG_SCNKEYCONFIG_H_
		void PrintRgsteredKey();	// �J�[�l����Ō��݂̃L�[�ݒ��\��
#endif
	};
}
