#include "ScnGameOver.h"
#include <iostream>

namespace scenes
{
	ScnGameOver::ScnGameOver(game::Game* game)
		:Scene(game)
	{
		ReadTextFile("assets/GameOver.txt");
	}

	void ScnGameOver::ProcessInput()
	{
		Scene::ProcessInput();

		const uint8_t* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			mIsRunning = false;
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

	void ScnGameOver::UpdateGame()
	{
		Scene::UpdateGame();
	}

	void ScnGameOver::GenerateOutput()
	{
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);
		RenderText(FONT_BBBOcelot_Regular, BLACK, "GAME OVER", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2));
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 140), static_cast<int>(HEIGHT / 2 + 45));
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2 + 80));
		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}

}
