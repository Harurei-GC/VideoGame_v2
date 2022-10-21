#pragma once
#include "SDL.h"


// ˆê‚Â‚Ì’l‚ğ•Û‚µ‚È‚ª‚çsetter‚Ægetter‚ğ’ñ‹Ÿ‚·‚éƒNƒ‰ƒX

class SG_Scancode
{
public:
	void Setter(SDL_Scancode k) { key = k; }
	SDL_Scancode Getter() { return key; }

private:
	SDL_Scancode key;
};