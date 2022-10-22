#include "scenes/ScnGameStart.h"
#include "game/Game.h"
#include <iostream>

namespace scenes
{
	ScnGameStart::ScnGameStart(game::Game* game)
		:Scene(game)
	{
		mIsRunning = true;
		ReadTextFile("assets/GameStart.txt");
	}

	void ScnGameStart::ProcessInput()
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
		}
		if (keyState[SDL_SCANCODE_K])
		{
			mIsRunning = false;
			mGame->SetKeyConfig(true);
		}
	}

	void ScnGameStart::UpdateGame()
	{
		Scene::UpdateGame();
	}

	void ScnGameStart::GenerateOutput()
	{
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);
		RenderText(FONT_BBBOcelot_Regular, BLACK, "Press ", static_cast<int>(WIDTH / 2 - 200), static_cast<int>(HEIGHT / 2));
		RenderText(FONT_BBBOcelot_Regular, RED, "Enter", static_cast<int>(WIDTH / 2 - 94), static_cast<int>(HEIGHT / 2));
		RenderText(FONT_BBBOcelot_Regular, BLACK, " to START!!", static_cast<int>(WIDTH / 2), static_cast<int>(HEIGHT / 2));
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 2);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 200), static_cast<int>(HEIGHT / 2 + 30));
		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}

}
