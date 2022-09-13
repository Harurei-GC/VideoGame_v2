#include "GameClear.h"

GameClear::GameClear(Game* game)
	:Scene(game)
{
}

void GameClear::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			mGame->SetQuitGame(true);
			break;
		}
	}

	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
		mGame->SetQuitGame(true);
	}
	if (keyState[SDL_SCANCODE_RETURN])
	{
		mIsRunning = false;
		mGame->SetQuitGame(true);
	}

}

void GameClear::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mGame->mTicksCount + 16));
	
	float deltaTime = (SDL_GetTicks() - mGame->mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mGame->mTicksCount = SDL_GetTicks();
}

void GameClear::GenerateOutput()
{
	SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mGame->gameRenderer);
	RenderText(FONT_BBBOcelot, BLACK, "GAME CLEAR!!", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2));
	SDL_RenderPresent(mGame->gameRenderer);
}

