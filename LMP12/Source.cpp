#include <iostream>
#include <Windows.h>
#include <omp.h>
#include <fstream>

int N, M;

int non_parallel(int** a)
{
	int mul = 1;
	for (int i = 0; i < N*M; i++)
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
	return mul;
}

int parallel(int** a)
{
	int global_mul=1;
	omp_lock_t lock; //содержит состо€ние блокировки
	omp_init_lock(&lock);
#pragma omp parallel shared(a)
	{
		int local_mul=1;
#pragma omp for schedule(static, 10)
		//разделение на порции.
		//количество потоков равно количеству логических потоков процессора. 
		//ѕри этом когда указываем количество элементов, разбиение по n элементов.
		//статик выдает по очереди, динамик в пор€дке обработки потоков.
		for (int i = 0; i < N * M; i++)
		{
			if (a[i / M][i % M] % 2 != a[i / M][i % M] / 10 % 2 && a[i / M][i % M] / 10 != 0)
			{
				int k = a[i / M][i % M];
				while (k / 10 > 0)
				{
					k = k / 10;
				}
				local_mul *= k;
			}
		}

		omp_set_lock(&lock);
		global_mul *= local_mul;
		//std::cout << local_mul << '\n';
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
	return global_mul;
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

	std::cout << non_parallel(arr) << '\n';
	std::cout << parallel(arr) << '\n';


	std::cin.get();
	return 0;
}