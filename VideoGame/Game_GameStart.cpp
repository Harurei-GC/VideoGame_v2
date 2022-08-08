#include "Game.h"

void Game::GameStart()
{
	// ProcessInput
	// イベント情報event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsStart = false;
			mIsRunning = false;
			break;
		}
	}

	// keyState:キーボード入力の状態を返す
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		// Escキー押すとゲームやめる
		mIsRunning = false;
	}
	if (keyState[SDL_SCANCODE_RETURN])
	{
		// ENTERキーでスタート
		mIsStart = false;
	}

	// UpdateGame
	// deltaTime計算
	// 最後のフレームから16ms経過するまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// SDLが初期化されてから今回までに経過した時間-前回までに経過した時間
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// GenerateOutput
	// 描画操作で使う色を設定する
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// Start描画
	mSurface[0] = TTF_RenderUTF8_Blended(mFont[FONT_BBBOcelot], "Press ENTER to START!!", mColor[BLACK]);
	mTexture[0] = SDL_CreateTextureFromSurface(mRenderer, mSurface[0]);
	int iw, ih;
	SDL_QueryTexture(mTexture[0], NULL, NULL, &iw, &ih);
	txtRectStr = SDL_Rect{ 0,0,iw,ih };
	pasteRectStr = SDL_Rect{ static_cast<int>(WIDTH / 2 -200),static_cast<int>(HEIGHT / 2),iw,ih };
	SDL_RenderCopy(mRenderer, mTexture[0], &txtRectStr, &pasteRectStr);

	// bufの一部文字列を表示させる
	char r[32];
	int i = 0;
	while (buf[i] != '\n')
	{
		r[i] = buf[i];
		i++;
	}
	mSurface[1] = TTF_RenderUTF8_Blended(mFont[FONT_PixelMplus], r, mColor[BLACK]);
	mTexture[1] = SDL_CreateTextureFromSurface(mRenderer, mSurface[1]);
	SDL_QueryTexture(mTexture[1], NULL, NULL, &iw, &ih);
	txtRectStr = SDL_Rect{ 0,0,iw,ih };
	pasteRectStr = SDL_Rect{ 100,100,iw,ih };
	SDL_RenderCopy(mRenderer, mTexture[1], &txtRectStr, &pasteRectStr);

	char q[32];
	int j = 0;
	i++;
	while (buf[i] != '\n')
	{
		q[j] = buf[i];
		j++;
		i++;
	}
	mSurface[2] = TTF_RenderUTF8_Blended(mFont[FONT_PixelMplus], q, mColor[BLACK]);
	mTexture[2] = SDL_CreateTextureFromSurface(mRenderer, mSurface[2]);
	SDL_QueryTexture(mTexture[2], NULL, NULL, &iw, &ih);
	txtRectStr = SDL_Rect{ 0,0,iw,ih };
	pasteRectStr = SDL_Rect{ 100,100 + ih,iw,ih };
	SDL_RenderCopy(mRenderer, mTexture[2], &txtRectStr, &pasteRectStr);


	// 画面に描画
	SDL_RenderPresent(mRenderer);
	// テキストの数だけメモリ解放
	for (int i = 0; i < 3; i++)
	{
		SDL_FreeSurface(mSurface[i]);
		SDL_DestroyTexture(mTexture[i]);
	}
}
