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
	mSurfaceStr = TTF_RenderUTF8_Blended(mFontStr, "Press ENTER to START!!", mColorStr);
	mTextureStr = SDL_CreateTextureFromSurface(mRenderer, mSurfaceStr);
	int iw, ih;
	SDL_QueryTexture(mTextureStr, NULL, NULL, &iw, &ih);
	txtRectStr = SDL_Rect{ 0,0,iw,ih };
	pasteRectStr = SDL_Rect{ static_cast<int>(WIDTH / 2 -200),static_cast<int>(HEIGHT / 2),iw,ih };
	SDL_RenderCopy(mRenderer, mTextureStr, &txtRectStr, &pasteRectStr);

	// 画面に描画
	SDL_RenderPresent(mRenderer);
}
