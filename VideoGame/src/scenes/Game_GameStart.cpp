#include "../Game.h"
#include <stdio.h>

void Game::GameStart()
{
	// ProcessInput
	// �C�x���g���event
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

	// keyState:�L�[�{�[�h���͂̏�Ԃ�Ԃ�
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		// Esc�L�[�����ƃQ�[����߂�
		mIsRunning = false;
	}
	if (keyState[SDL_SCANCODE_RETURN])
	{
		// ENTER�L�[�ŃX�^�[�g
		mIsStart = false;
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

	// Start�`��
	RenderText(FONT_BBBOcelot, BLACK, "Press ENTER to START!!", static_cast<int>(WIDTH / 2 - 200),static_cast<int>(HEIGHT / 2));

	DispTextfile(FONT_PixelMplus, BLACK, 100, 100);
	DispTextfile(FONT_PixelMplus, BLACK, 100, 100 + ih);
	DispTextfile(FONT_PixelMplus, BLACK, 100, 100 + ih*2);
	DispTextfile(FONT_PixelMplus, BLACK, 100, 100 + ih * 3);

	// ��ʂɕ`��
	SDL_RenderPresent(mRenderer);
	bufCount = 0;
}

void Game::DispTextfile(int font, int color, int rw, int rh)
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