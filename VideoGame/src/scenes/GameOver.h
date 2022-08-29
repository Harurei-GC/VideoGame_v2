#pragma once
#include "Scene.h"

class GameOver :public Scene
{
public:
	GameOver(Game* game);
	void ProcessInput()override;
	void UpdateGame()override;
	void GenerateOutput()override;
private:
};