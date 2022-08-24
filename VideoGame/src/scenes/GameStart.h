#pragma once
#include "Scene.h"

class GameStart :public Scene
{
public:
	GameStart();
	void ProcessInput()override;
	void UpdateGame()override;
	void GeneralOutput()override;
};