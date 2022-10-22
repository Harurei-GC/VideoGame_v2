#pragma once
#include "SDL.h"


// 一つの値を保持しながらsetterとgetterを提供するクラス

class SG_Scancode
{
public:
	void Setter(SDL_Scancode k) { key = k; }
	SDL_Scancode Getter() { return key; }

private:
	SDL_Scancode key;
};