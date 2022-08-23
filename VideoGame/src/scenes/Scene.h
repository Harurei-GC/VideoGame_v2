#pragma once
#include "../Game.h"

class Scene
{
public:
	Scene();
	void RunLoop();
	virtual void ProcessInput(){}
	virtual void UpdateGame(){}
	virtual void GeneralOutput(){}
	void SetIsRunning(bool is) { mIsRunning = is; }
	bool GetIsRunning() { return mIsRunning; }
private:
	bool mIsRunning;
};
