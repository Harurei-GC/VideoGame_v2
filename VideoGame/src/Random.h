#pragma once

class Random
{
public:
	Random();
	// a~z�܂ł̃����_���Ȑ�����Ԃ�
	static int Sampling(int a, int z);
private:
	int count;
};