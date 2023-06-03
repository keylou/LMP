#include "ThreadSafeQueue.h"
#include <thread>
#include <mutex>
#include <condition_variable>


ThreadSafeQueue queue;
volatile long gl_mul = 1;
volatile long lock = 0;
volatile long volume_work_producer = 5; 
volatile long volume_work_consumer = 5;
//есть 10 порций работы, поэтому 10 раз мы должны их положить и 10 раз обработать.
std::condition_variable cv; //переменная состояния контейнера(охраняет доступ к данным)
std::mutex mut;


//18. Дана прямоугольная целочисленная матрица. 
// Распараллеливание по элементам. 
// Найти произведение старших разрядов тех чисел, 
// в которых первый две цифры разной четности.
//    событие + очередь

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
	// пока есть работа у потока-производителя
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		// формируются элементы для последующей обработки
		// потоком-потребителем
		Segment tmp;
		for (int i = 0; i < block; i++)
		{
			tmp.array[i] = rand() % 30 + 10 + ID;
		}
		Sleep(2);
		queue.push(tmp);
		// поток-производитель передает сигнал,
		// что в контейнере появился элемент для обработки
		cv.notify_all();
	}
}


void task_consumer(int ID)
{
	// пока есть работа у потока-потребителя
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		Segment tmp;
		// контроллирует общий ресурс
		// условные переменные работают только с мьютексом.
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5),
			[]() {return !queue.is_empty(); });
		if (queue.pop(tmp))
		{
			// если элемент извлечен из контейнера,
			//то он обрабатывается потоком-потребителем
			Sleep(5);
			while (_InterlockedCompareExchange(&lock, 1, 0))
				Sleep(0);
			gl_mul *= multiply(tmp);
			_InterlockedCompareExchange(&lock, 0, 1);
		}
		else
		{
			// работа не выполнена, объем работы потребителя
			// возвращается в исходное состояние
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

void multiply_p()
{
	// создание потоков:
	// 4 потока-производителя (producer);
	// 3 потока-потребителя (consumer);
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