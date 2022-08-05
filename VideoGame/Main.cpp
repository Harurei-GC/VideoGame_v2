#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	// ƒQ[ƒ€‚Ì‹N“®‚É¬Œ÷‚µ‚½‚©
	bool success = game.Initialize();
	if (success) 
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}