#pragma once
#include "scenes/Scene.h"

namespace scenes
{
	class GameStart :public Scene
	{
	public:
		GameStart(game::Game* game);
		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;

		// buf‚Ìˆê•”•¶Žš—ñ‚ð•\Ž¦‚³‚¹‚é
		void DispSentenceFromFile(int font, int color, int rw, int rh);
	private:
		int bufCount;
		char buf[1024];
		FILE* fp;
	};
}
