#include "game/Game.h"

int main(int argc, char** argv)
{
	game::Game game;
	// ƒQ[ƒ€‚Ì‹N“®‚É¬Œ÷‚µ‚½‚©
	bool success = game.Initialize();
	if (success) 
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}