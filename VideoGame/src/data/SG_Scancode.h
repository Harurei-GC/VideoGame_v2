#pragma once
#include "SDL.h"


// ��̒l��ێ����Ȃ���setter��getter��񋟂���N���X

class SG_Scancode
{
public:
	void Setter(SDL_Scancode k) { key = k; }
	SDL_Scancode Getter() { return key; }

private:
	SDL_Scancode key;
};