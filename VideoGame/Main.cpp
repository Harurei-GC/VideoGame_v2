#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	// �Q�[���̋N���ɐ���������
	bool success = game.Initialize();
	if (success) 
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}