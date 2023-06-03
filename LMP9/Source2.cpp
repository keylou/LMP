#include <iostream>
#include <fstream>
#include <future>

size_t N;
size_t M;
const size_t NTHREAD = 5;

struct Mul_Elem
{
	int mul;
};

Mul_Elem multiply(int** a, int beg, int end)
{
	Mul_Elem el;
	el.mul = 1;
	for (int i = beg; i < end; i++)
	{
		if (a[i / M][i % M] % 2 != a[i / M][i % M] / 10 % 2 && a[i / M][i % M] / 10 != 0)
		{
			int k = a[i / M][i % M];
			while (k / 10 > 0)
			{
				k = k / 10;
			}
			el.mul *= k;
		}
	}
	return el;
}

Mul_Elem multiply_p(int** a)
{
	std::future<Mul_Elem> TH[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::async(multiply, a, i * n, N * M);
		else
			TH[i] = std::async(multiply, a, i * n, (i + 1) * n);
	}

	Mul_Elem res;
	res.mul = 1;

	Mul_Elem tmp;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		tmp = TH[i].get();
		res.mul *= tmp.mul;
	}

	return res;
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

	std::cout << multiply_p(arr).mul;
}