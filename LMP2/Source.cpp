#include "My_List.h"
#include <Windows.h>

using namespace std;

void task(DLIST& dl)
{
	ptrNODE left = dl.get_begin();
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ifstream file("bus.txt");
	DLIST dl("bus.txt");
	task(dl);

	std::cin.get();
}