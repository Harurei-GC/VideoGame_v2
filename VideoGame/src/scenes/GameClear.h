#pragma once
#include "Scene.h"

namespace scenes
{
	class GameClear :public Scene
	{
	public:
		GameClear(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:
	};
}
