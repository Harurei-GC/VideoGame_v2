#include "game/Game.h"

int main(int argc, char** argv)
{
	game::Game game;
	// ゲームの起動に成功したか
	bool success = game.Initialize();
	if (success) 
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}