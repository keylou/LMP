//18. ���� ������������� ������������� �������. ����������������� �� ���������. ����� ������������
//    ������� �������� ��� �����, � ������� ������ ��� ����� ������ ��������.
//    ������� + �������


#pragma once
#include <queue>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <utility>
using std::queue;
using std::pair;

const int block = 3;

struct Piece
{
	int array[block];
	Piece()
	{
		for (int i = 0; i < block; i++)
		{
			array[i] = 0;
		}
	}
	Piece(const Piece& p)
	{
		for (int i = 0; i < block; i++)
		{
			this->array[i] = p.array[i];
		}
	}
	Piece& operator=(const Piece &p)
	{
		if (this != &p)
		{
			for (int i = 0; i < block; i++)
			{
				this->array[i] = p.array[i];
			}
		}
		return *this;
	}
	friend std::ostream& operator<< (std::ostream& out, const Piece p)
	{
		for (int i = 0; i < block; i++)
		{
			out << p.array[i] << " ";
		}
		out << '\n';
		return out;
	}
};

using Segment = Piece;

class ThreadSafeQueue {
private:
	std::queue <Segment> q;
	HANDLE HEvent;
public:
	ThreadSafeQueue() {
		HEvent = CreateEvent(nullptr, false, true, nullptr);
		//������ ���� --> ������� ����������������, � ����� ����������.
		//������� ������: null <-> ������� �� ��������� [handle �� ����� ���� ����������� �������� �������],
		//������ ��� ������: false <-> ������� ���� ���������� � ������������� ��������� �����,
		//��������� ��������� �������,
		//��� �������
	}
	~ThreadSafeQueue() {
		CloseHandle(HEvent);
	}
	bool is_empty() const {
		return q.empty();
	}
	bool pop(Segment& s) {
		bool result = false;
		if (WaitForSingleObject(HEvent, INFINITE) == WAIT_OBJECT_0) { //���� ���� ������� �������� � ���, ��� ������� ������ ������ �� �����
			try
			{
				if (!q.empty())
				{
					result = true;
					s = q.front();
					std::cout << s;
					q.pop();
				}
			}
			//error_mes - ��������� � ���, ��� ��������� - �������������, �� �������� �����
			catch (std::string error_mess) {
				//��������������� ������������ ����������� ������ ��� ����� ������
				SetEvent(HEvent);
				throw error_mess;
			}
			SetEvent(HEvent);
		}
		return result;
	}
	void push(Segment s)
	{
		if (WaitForSingleObject(HEvent, INFINITE) == WAIT_OBJECT_0) 
		{
			try
			{
				q.push(s);
			}
			catch (...)
			{
				SetEvent(HEvent);
			}
			SetEvent(HEvent);
		}
	}
};