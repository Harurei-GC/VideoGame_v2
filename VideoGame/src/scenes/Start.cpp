#include "Start.h"
#include <iostream>

Start::Start(Game* game)
	:Scene(game)
	,bufCount(0)
{
	mIsRunning = true;
	// テキストファイル読み込み
	// なぜかコマンドラインに表示される
	if (fopen_s(&fp, "assets/Text.txt", "r") != 0)
	{
		std::cout << "Failed to open a text file" << std::endl;
	}
	else
	{
		int i = 0;
		while ((buf[i] = fgetc(fp)) != EOF)
		{
			putchar(buf[i]);
			i++;
		}
		fclose(fp);
	}
}

void Start::ProcessInput()
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
		mGame->SetQuitGame(true);
	}
	if (keyState[SDL_SCANCODE_RETURN])
	{
		mIsRunning = false;
	}
}

void Start::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mGame->mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mGame->mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mGame->mTicksCount = SDL_GetTicks();
}

void Start::GenerateOutput()
{
	SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mGame->gameRenderer);
	RenderText(FONT_BBBOcelot, BLACK, "Press Enter to START!!", static_cast<int>(WIDTH / 2 - 200), static_cast<int>(HEIGHT / 2));
	DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100);
	DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH);
	DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 2);
	DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + texH * 3);
	SDL_RenderPresent(mGame->gameRenderer);
	bufCount = 0;
}


void Start::DispSentenceFromFile(int font, int color, int rw, int rh)
{
	char r[64] = { 0 };
	if (bufCount != 0)
	{
		bufCount++;
	}
	int i = 0;
	while (buf[bufCount] != '\n')
	{
		if (bufCount > sizeof(buf)) { break; }
		r[i] = buf[bufCount];
		i++;
		bufCount++;
	}
	RenderText(font, color, r, rw, rh);
}