#include <time.h>
#include "Random.h"
#include <iostream>
#include <stdlib.h>

Random::Random()
:count(0)
{
}

// a~zまでのランダムな数字を返す
// HACK:完全なランダムではない、もう少し改良したい
int Random::Sampling(int a, int z)
{
	int r = rand();
	return (((int)clock())+r) % (z - a + 1) + a;
}