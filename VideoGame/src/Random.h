#pragma once

class Random
{
public:
	Random();
	// a~z�܂ł̃����_���Ȑ�����Ԃ�
	int Sampling(int a, int z);
private:
	int count;
};