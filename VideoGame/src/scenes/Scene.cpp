#include "Scene.h"

Scene::Scene()
	:mIsRunning(false)
{

}

// NOTE:�h���N���X�ɂ�����UpdateGame()�Ȃǂ�override�֐���ǂݍ��ނ悤�ɂ�����
void Scene::RunLoop()
{
	ProcessInput();
	UpdateGame();
	GeneralOutput();
}