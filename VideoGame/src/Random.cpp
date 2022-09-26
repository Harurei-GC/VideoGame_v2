#include <time.h>
#include "Random.h"
#include <iostream>
#include <stdlib.h>

Random::Random()
:count(0)
{
}

// a~zまでのランダムな数字を返す
// a>zの場合、z~aまでのランダムな数字が返される
int Random::Sampling(int a, int z)
{
	int r = rand();
	if (a > z+1)
	{	// NOTE:マイナス余剰計算を知らせるための処理
		std::cout << "Random.cpp error: 第一引数が第二引数よりも大きいです。 (a=" << a << ", z =" << z << " )" << std::endl;
	}
	return (((int)clock())+r) % (z - a + 1) + a;
}