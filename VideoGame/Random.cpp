#include <time.h>
#include "Random.h"
#include <iostream>


Random::Random()
:count(0)
{
}

// a~z�܂ł̃����_���Ȑ�����Ԃ�
// HACK:���S�ȃ����_���ł͂Ȃ��A�����������ǂ�����
int Random::Sampling(int a, int z)
{
	//t = clock();
	//count += 1; �Ȃ����o�O��
	return ((int)clock()) % (z - a + 1) + a;
}