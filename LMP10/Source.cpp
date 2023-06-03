#include <iostream>
#include <fstream>
#include <thread>
#include <Windows.h>

size_t N;
size_t M;
const size_t NTHREAD = 6;
volatile long lock = 0;

void multiply(int** a, int beg, int end, volatile long& mul)
{
	int loc_mul = 1;
	for (int i = beg; i < end; i++)
	{
		if (a[i / M][i % M] % 2 != a[i / M][i % M] / 10 % 2 && a[i / M][i % M] / 10 != 0)
		{
			int k = a[i / M][i % M];
			while (k / 10 > 0)
			{
				k = k / 10;
			}
			loc_mul *= k;
		}
	}

	if (loc_mul > 1)
	{
		while (_InterlockedCompareExchange(&lock, 1, 0))
			Sleep(0);
		mul *= loc_mul;
		_InterlockedCompareExchange(&lock, 0, 1);
	}
}

int multiply_p(int** a)
{
	std::thread TH[NTHREAD-1];
	volatile long mul=1;
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD-1; i++)
	{
		TH[i] = std::thread(multiply, a, i * n, (i + 1) * n, std::ref(mul));
	}

	multiply(a, (NTHREAD - 1) * n, N*M, mul);

	for (size_t i = 0; i < NTHREAD-1; i++)
	{
		TH[i].join();
	}

	return mul;
}

int main()
{
	std::ifstream input("input.txt");
	input >> N >> M;
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];
	for (int i = 0; i < N * M; i++)
		input >> arr[i / M][i % M];
	input.close();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			std::cout << arr[i][j] << " ";
		std::cout << '\n';
	}

	std::cout << multiply_p(arr);
}
