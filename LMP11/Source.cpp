#include "ThreadSafeQueue.h"
#include <thread>
#include <mutex>
#include <condition_variable>


ThreadSafeQueue queue;
volatile long gl_mul = 1;
volatile long lock = 0;
volatile long volume_work_producer = 5; 
volatile long volume_work_consumer = 5;
//���� 10 ������ ������, ������� 10 ��� �� ������ �� �������� � 10 ��� ����������.
std::condition_variable cv; //���������� ��������� ����������(�������� ������ � ������)
std::mutex mut;


//18. ���� ������������� ������������� �������. 
// ����������������� �� ���������. 
// ����� ������������ ������� �������� ��� �����, 
// � ������� ������ ��� ����� ������ ��������.
//    ������� + �������

int multiply(Segment s)
{
	int loc_mul = 1;
	for (int i = 0; i < block; i++)
	{
		if (s.array[i] % 2 != s.array[i] / 10 % 2 && s.array[i] / 10 != 0)	
		{
			int k = s.array[i];
			while (k / 10 > 0)
			{
				k = k / 10;
			}
			loc_mul *= k;
		}
	}
	return loc_mul;
}

void task_producer(int ID)
{
	// ���� ���� ������ � ������-�������������
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		// ����������� �������� ��� ����������� ���������
		// �������-������������
		Segment tmp;
		for (int i = 0; i < block; i++)
		{
			tmp.array[i] = rand() % 30 + 10 + ID;
		}
		Sleep(2);
		queue.push(tmp);
		// �����-������������� �������� ������,
		// ��� � ���������� �������� ������� ��� ���������
		cv.notify_all();
	}
}


void task_consumer(int ID)
{
	// ���� ���� ������ � ������-�����������
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		Segment tmp;
		// ������������� ����� ������
		// �������� ���������� �������� ������ � ���������.
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5),
			[]() {return !queue.is_empty(); });
		if (queue.pop(tmp))
		{
			// ���� ������� �������� �� ����������,
			//�� �� �������������� �������-������������
			Sleep(5);
			while (_InterlockedCompareExchange(&lock, 1, 0))
				Sleep(0);
			gl_mul *= multiply(tmp);
			_InterlockedCompareExchange(&lock, 0, 1);
		}
		else
		{
			// ������ �� ���������, ����� ������ �����������
			// ������������ � �������� ���������
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

void multiply_p()
{
	// �������� �������:
	// 4 ������-������������� (producer);
	// 3 ������-����������� (consumer);
	std::thread worker[7];

	for (int i = 0; i < 7; i++)
		if (i < 4)
			worker[i] = std::thread(task_producer, i);
		else
			worker[i] = std::thread(task_consumer, i);

	for (int i = 0; i < 7; i++)
	{
		worker[i].join();
	}
}

int main()
{
	multiply_p();
	std::cout << gl_mul;
	std::cin.get();
}