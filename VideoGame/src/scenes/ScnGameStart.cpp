#include "scenes/ScnGameStart.h"
#include "game/Game.h"
#include <iostream>
#include "data/KeyData.h"

namespace scenes
{
	ScnGameStart::ScnGameStart(game::Game* game)
		:Scene(game)
	{
		mIsRunning = true;
		ReadTextFile("assets/GameStart.txt");
		mKeyData = mGame->GetKeyData();
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
		RenderText(FONT_PixelMplus, BLACK, SDL_GetScancodeName(mKeyData->GetResetKey().Getter()), 100, 100);			// R
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100 + texW*5, 100);												// 位置リセット
		RenderText(FONT_PixelMplus, BLACK, SDL_GetScancodeName(mKeyData->GetUpKey().Getter()), 100, 100+texH);				// W
		RenderText(FONT_PixelMplus, BLACK, SDL_GetScancodeName(mKeyData->GetDownKey().Getter()), 100 + texW, 100+texH);		// S
		RenderText(FONT_PixelMplus, BLACK, SDL_GetScancodeName(mKeyData->GetRightKey().Getter()), 100 + texW*2, 100+texH);	// A
		RenderText(FONT_PixelMplus, BLACK, SDL_GetScancodeName(mKeyData->GetLeftKey().Getter()), 100 + texW*3, 100+texH);	// D
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100 + texW * 5, 100 + texH);										// 移動
		RenderText(FONT_PixelMplus, BLACK, "Esc  ", 100, 100 + texH * 2);												// Esc
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100 + texW, 100 + texH * 2);										// やめる
		DispSentenceFromFile(FONT_PixelMplus, BLACK, static_cast<int>(WIDTH / 2 - 200), static_cast<int>(HEIGHT / 2 + 30));	// Kキーでキーコンフィグ
		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}

}
