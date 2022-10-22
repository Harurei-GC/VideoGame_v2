#include "scenes/ScnGameClear.h"
#include "game/Game.h"
#include <iostream>

namespace scenes
{
	ScnGameClear::ScnGameClear(game::Game* game)
		:Scene(game)
		,mScore(Score::C)
	{
		ReadTextFile("assets/GameClear.txt");
	}

	void ScnGameClear::ProcessInput()
	{
		Scene::ProcessInput();

		const uint8_t* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			mIsRunning = false;
			mGame->SetQuitGame(true);
		}
		if (keyState[SDL_SCANCODE_RETURN])
		{
			mIsRunning = false;
			mGame->SetPlayAgain(true);
		}
		if (keyState[SDL_SCANCODE_K])
		{
			mIsRunning = false;
			mGame->SetKeyConfig(true);
		}

	}

	void ScnGameClear::UpdateGame()
	{
		Scene::UpdateGame();
	}

	void ScnGameClear::GenerateOutput()
	{
		// スコアごとに適切な値の代入
		int scoreColor = BLACK;
		const char* score = nullptr;
		switch (mScore)
		{
		case Score::A:
			scoreColor = RED;
			score = "A";
			break;
		case Score::B:
			scoreColor = BLUE;
			score = "B";
			break;
		case Score::C:
			scoreColor = YELLOW;
			score = "C";
			break;
		}

		// レンダリング
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);
		RenderText(FONT_BBBOcelot_Regular, BLACK, "GAME CLEAR!!", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2));
		RenderText(FONT_BBBOcelot_Regular, BLACK, "SCORE: ", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2 + 50));
		RenderText(FONT_BBB_Simulator_Black, scoreColor, score, static_cast<int>(WIDTH / 2 + 50), static_cast<int>(HEIGHT / 2 + 35));
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2 + 100));
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2 + 135));
		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}


}

