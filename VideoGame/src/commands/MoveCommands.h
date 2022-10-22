#pragma once
#include "Command.h"
#include "actors/Actor.h"
#include "components/InputComponent.h"

// 移動に関する様々なクラスを記述したヘッダファイルです。

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