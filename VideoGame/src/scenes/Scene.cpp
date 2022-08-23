#include "Scene.h"

Scene::Scene()
	:mIsRunning(false)
{

}

// NOTE:”h¶ƒNƒ‰ƒX‚É‚¨‚¢‚ÄUpdateGame()‚È‚Ç‚ÌoverrideŠÖ”‚ğ“Ç‚İ‚Ş‚æ‚¤‚É‚µ‚½‚¢
void Scene::RunLoop()
{
	ProcessInput();
	UpdateGame();
	GeneralOutput();
}