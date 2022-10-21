#pragma once
#include <stdint.h>
#include "game/Game.h"
#include "SG_Scancode.h"

namespace data
{
	// �L�[�R���t�B�O�̌��ʂ�ێ�����N���X
	// Game�N���X�ł̂݃C���X�^���X����


	enum class KeyType
	{// �L�[�R���t�B�O�ŕύX�ł��鑀��
		UP,
		DOWN,
		RIGHT,
		LEFT,
		RESET
	};

	class KeyData
	{
	public:
		KeyData();
		~KeyData();

		SG_Scancode GetUpKey() { return mUpKey; }
		SG_Scancode GetDownKey() { return mDownKey; }
		SG_Scancode GetRightKey() { return mRightKey; }
		SG_Scancode GetLeftKey() { return mLeftKey; }
		SG_Scancode GetResetKey() { return mResetKey; }

		SG_Scancode* GetPtrUpKey() { return &mUpKey; }
		SG_Scancode* GetPtrDownKey() { return &mDownKey; }
		SG_Scancode* GetPtrRightKey() { return &mRightKey; }
		SG_Scancode* GetPtrLeftKey() { return &mLeftKey; }
		SG_Scancode* GetPtrResetKey() { return &mResetKey; }

	private:
		SG_Scancode mUpKey;
		SG_Scancode mDownKey;
		SG_Scancode mRightKey;
		SG_Scancode mLeftKey;
		SG_Scancode mResetKey;
	};
}
