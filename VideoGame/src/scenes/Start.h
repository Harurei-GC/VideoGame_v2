#pragma once
#include "Scene.h"

class Start :public Scene
{
public:
	Start(Game* game);
	void ProcessInput()override;
	void UpdateGame()override;
	void GenerateOutput()override;
private:

	// buf�̈ꕔ�������\��������
	void DispSentenceFromFile(int font, int color, int rw, int rh);

	int bufCount;
	char buf[1024];
	FILE* fp;
};