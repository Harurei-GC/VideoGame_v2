#pragma once
#include "Scene.h"

namespace scenes
{
	enum class Score
	{
		A,
		B,
		C
	};

	class ScnGameClear :public Scene
	{
	public:
		ScnGameClear(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
		void SetScore(Score s) { mScore = s; }
	private:
		Score mScore;
	};
}
