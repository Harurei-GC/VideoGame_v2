#include "../Game.h"

// NOTE:gameclearとgameoverを適切に書き換える。
// また、ここら辺gameclearとgameoverとgamestartのコードが似通っている。
// そのため、関数にカプセル化しておきたい。
void Game::GameClear()
{
	// ProcessInput
	// イベント情報event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsCleared = false;
			break;
		}
	}

	// keyState:キーボード入力の状態を返す
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RETURN])
	{
		// ENTERキーで終了
		mIsCleared = false;
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

	// GameClear描画
	RenderText(FONT_BBBOcelot, BLACK, "GAME CLEAR!!", static_cast<int>(WIDTH / 2 - 100), static_cast<int>(HEIGHT / 2));

	// 画面に描画
	SDL_RenderPresent(mRenderer);

}