#pragma once

namespace math
{
	class Random
	{
	public:
		Random();
		// a~zまでのランダムな数字を返す
		static int Sampling(int a, int z);
	private:
		int count;
	};
}
