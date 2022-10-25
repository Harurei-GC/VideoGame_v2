#pragma once
#include "scenes/Scene.h"

namespace scenes
{
	class ScnGameStart :public Scene
	{
	public:
		ScnGameStart(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;

	private:
		data::KeyData* mKeyData;
	};
}
