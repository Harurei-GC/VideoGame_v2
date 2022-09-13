#include "GameOver.h"

GameOver::GameOver(Game* game)
	:Scene(game)
{
}

void GameOver::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	if (keyState[SDL_SCANCODE_RETURN])
	{
		mIsRunning = false;
	}
}

void GameOver::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mGame->mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mGame->mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mGame->mTicksCount = SDL_GetTicks();
}

void GameOver::GenerateOutput()
{
	SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mGame->gameRenderer);
	RenderText(FONT_BBBOcelot, BLACK, "GAME OVER", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2));
	SDL_RenderPresent(mGame->gameRenderer);
}