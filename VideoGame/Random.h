#pragma once

class Random
{
public:
	Random();
	// a~z�܂ł̃����_���Ȑ�����Ԃ�
	// HACK:���S�ȃ����_���ł͂Ȃ��A�����������ǂ�����
	int Sampling(int a, int z);
private:
	int count;
	//time_t t;
};