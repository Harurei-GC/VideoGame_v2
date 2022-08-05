#include <time.h>
#include "Random.h"
#include <iostream>


Random::Random()
:count(0)
{
}

// a~zまでのランダムな数字を返す
// HACK:完全なランダムではない、もう少し改良したい
int Random::Sampling(int a, int z)
{
	//t = clock();
	//count += 1; なぜかバグる
	return ((int)clock()) % (z - a + 1) + a;
}