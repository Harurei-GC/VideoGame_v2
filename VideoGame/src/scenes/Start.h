#pragma once
#include "Scene.h"

class Start :public Scene
{
public:
	Start(Game* game);
	void ProcessInput()override;
	void UpdateGame()override;
	void GenerateOutput()override;

	// bufの一部文字列を表示させる
	void DispSentenceFromFile(int font, int color, int rw, int rh);
private:
	int bufCount;
	char buf[1024];
	FILE* fp;
};