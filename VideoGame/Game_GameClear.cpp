#include "Game.h"

// NOTE:gameclear��gameover��K�؂ɏ���������B
// �܂��A�������gameclear��gameover��gamestart�̃R�[�h�����ʂ��Ă���B
// ���̂��߁A�֐��ɃJ�v�Z�������Ă��������B
void Game::GameClear()
{
	// ProcessInput
	// �C�x���g���event
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

	// keyState:�L�[�{�[�h���͂̏�Ԃ�Ԃ�
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RETURN])
	{
		// ENTER�L�[�ŏI��
		mIsCleared = false;
	}

	// UpdateGame
	// deltaTime�v�Z
	// �Ō�̃t���[������16ms�o�߂���܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// SDL������������Ă��獡��܂łɌo�߂�������-�O��܂łɌo�߂�������
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// GenerateOutput
	// �`�摀��Ŏg���F��ݒ肷��
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// GameClear�`��
	mSurfaceStr = TTF_RenderUTF8_Blended(mFontStr, "GAME CLEAR!!", mColorStr);
	mTextureStr = SDL_CreateTextureFromSurface(mRenderer, mSurfaceStr);
	int iw, ih;
	SDL_QueryTexture(mTextureStr, NULL, NULL, &iw, &ih);
	txtRectStr = SDL_Rect{ 0,0,iw,ih };
	pasteRectStr = SDL_Rect{ static_cast<int>(WIDTH / 2 -100),static_cast<int>(HEIGHT / 2),iw,ih };
	SDL_RenderCopy(mRenderer, mTextureStr, &txtRectStr, &pasteRectStr);

	// ��ʂɕ`��
	SDL_RenderPresent(mRenderer);
}