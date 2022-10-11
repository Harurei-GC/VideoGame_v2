#pragma once
#include "Scene.h"

namespace scenes
{
	class GameOver :public Scene
	{
	public:
		GameOver(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:
	};
}
