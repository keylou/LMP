#include <iostream>
#include <fstream>
#include <thread>

size_t N;
size_t M;
const size_t NTHREAD = 6;

void multiply(int** a, int beg, int end, int& mul)
{
	mul = 1;
	for (int i = beg; i < end; i++)
	{
		if (a[i / M][i % M] % 2 != a[i / M][i % M] / 10 % 2 && a[i / M][i % M] / 10 != 0)
		{
			int k = a[i / M][i % M];
			while (k / 10 > 0)
			{
				k = k / 10;
			}
			mul *= k;
		}
	}
}

int multiply_p(int** a)
{
	std::thread TH[NTHREAD];
	int mul[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::thread(multiply, a, i * n, N * M, std::ref(mul[i]));
		else
			TH[i] = std::thread(multiply, a, i * n, (i + 1) * n, std::ref(mul[i]));
	}
	for (int i = 0; i < NTHREAD; i++)
		TH[i].join();

	int gl_mul = mul[0];

	for (size_t i = 1; i < NTHREAD; i++)
	{
		gl_mul *= mul[i];
	}

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

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			std::cout << arr[i][j] << " ";
		std::cout << '\n';
	}

	std::cout << multiply_p(arr);
}