#pragma once

class Random
{
public:
	Random();
	// a~zまでのランダムな数字を返す
	int Sampling(int a, int z);
private:
	int count;
};