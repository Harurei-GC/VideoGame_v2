#pragma once

class Random
{
public:
	Random();
	// a~zまでのランダムな数字を返す
	// HACK:完全なランダムではない、もう少し改良したい
	int Sampling(int a, int z);
private:
	int count;
	//time_t t;
};