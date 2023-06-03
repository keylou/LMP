#include "My_List.h"
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

void task(LIST l, function<bool(ptrNODE&)> lambda)
{
	ptrNODE first = nullptr, last = nullptr, ptr = l.get_head();
	while (ptr->next)
	{
		if (lambda(ptr->next))
			if (first == nullptr)
			{
				first = ptr;
			}
			else if (last == nullptr)
			{
				last = ptr->next;
			}
			else
			{
				first = last;
				last = ptr->next;
			}
		ptr = ptr->next;
	}
	if (first && last)
		while (first->next != last)
			l.del_after(first);
	l.del_after(first);
}

int main()
{
	LIST l;
	ifstream f("test.txt");
	l.create_by_queue(f);
	l.print();
	auto lamda = [](ptrNODE& ptr) {return ptr->info % 10 == 7; };
	task(l, lamda);
	l.print();
}