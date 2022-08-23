#include "Scene.h"

Scene::Scene()
	:mIsRunning(false)
{

}

// NOTE:派生クラスにおいてUpdateGame()などのoverride関数を読み込むようにしたい
void Scene::RunLoop()
{
	ProcessInput();
	UpdateGame();
	GeneralOutput();
}