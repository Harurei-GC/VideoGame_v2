#include <time.h>
#include "Random.h"
#include <iostream>
#include <stdlib.h>

Random::Random()
:count(0)
{
}

// a~z�܂ł̃����_���Ȑ�����Ԃ�
// HACK:���S�ȃ����_���ł͂Ȃ��A�����������ǂ�����
int Random::Sampling(int a, int z)
{
	int r = rand();
	return (((int)clock())+r) % (z - a + 1) + a;
}