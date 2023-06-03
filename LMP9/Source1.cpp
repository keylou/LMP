#include <iostream>
#include <Windows.h>
#include <fstream>
#include <process.h>

size_t N;
size_t M;
const size_t NTHREAD = 5;

using INFORM = struct elem
{
	int** a;
	size_t beg, end;
	int mul = 0;
};

unsigned __stdcall multiply(void* a)
{
	INFORM* inform = (INFORM*)a;
	inform->mul = 1;
	for (int i = inform->beg; i < inform->end; i++)
	{
		if (inform->a[i / M][i % M] % 2 != inform->a[i / M][i % M] / 10 % 2 && inform->a[i / M][i % M] / 10 != 0)
		{
			int k = inform->a[i / M][i % M];
			while (k / 10 > 0)
			{
				k = k / 10;
			}
			inform->mul *= k;
		}
	}
	_endthreadex(0);
	return 0;
}

int multiply_p(int** a)
{
	HANDLE TH[NTHREAD];
	unsigned THID[NTHREAD];
	INFORM inform[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		inform[i].a = a;
		inform[i].beg = i * n;
		inform[i].mul = 0;
		if (i == NTHREAD - 1)
			inform[i].end = N * M;
		else
			inform[i].end = (i + 1) * n;
		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &multiply, &inform[i], 0, nullptr);
	}
	WaitForMultipleObjects(NTHREAD, TH, true, INFINITE);

	int gl_mul = inform[0].mul;

	for (size_t i = 1; i < NTHREAD; i++)
	{
		gl_mul *= inform[i].mul;
	}

	for (size_t i = 0; i < NTHREAD; i++)
		CloseHandle(TH[i]);

	return gl_mul;
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

	std::cout << multiply_p(arr);
}