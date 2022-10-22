#pragma once
#include "Scene.h"

namespace scenes
{
	class ScnGameOver :public Scene
	{
	public:
		ScnGameOver(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:
	};
}
