#pragma once
#include "Command.h"
#include "actors/Actor.h"
#include "components/InputComponent.h"

// �ړ��Ɋւ���l�X�ȃN���X���L�q�����w�b�_�t�@�C���ł��B

namespace commands
{
	class CmdUpToMove :public Command
	{
		void execute(actors::Actor* actor)override
		{
			//actor->GetInput()->SetUpKey();
		}
	};
}