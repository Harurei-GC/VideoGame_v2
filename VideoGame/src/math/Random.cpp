#include <time.h>
#include "Random.h"
#include <iostream>
#include <stdlib.h>

namespace math
{
	Random::Random()
	:count(0)
	{
	}

	// a~z�܂ł̃����_���Ȑ�����Ԃ�
	// a>z�̏ꍇ�Az~a�܂ł̃����_���Ȑ������Ԃ����
	int Random::Sampling(int a, int z)
	{
		int r = rand();
		if (a > z+1)
		{	// NOTE:�}�C�i�X�]��v�Z��m�点�邽�߂̏���
			std::cout << "Random.cpp error: �������������������傫���ł��B (a=" << a << ", z =" << z << " )" << std::endl;
		}
		if ((z - a + 1) == 0) { ++z; }
		return (((int)clock())+r) % (z - a + 1) + a;
	}
}
