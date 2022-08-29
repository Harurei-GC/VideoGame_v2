#pragma once
#include "Scene.h"

class GameClear :public Scene
{
public:
	GameClear(Game* game);
	void ProcessInput()override;
	void UpdateGame()override;
	void GenerateOutput()override;
private:
};