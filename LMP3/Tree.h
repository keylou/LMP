#pragma once
#include <iostream>
#include <fstream>
#include <string>

using TInfo = char;

struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level = 0)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}

using TElem = Tree;

Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree root = new NODE(' ');
	if (c >= '0' && c <= '9')
		root->info = c;
	else
	{
		root->left = Build_Formula(file);
		root->info = file.get();
		root->right = Build_Formula(file);
		c = file.get();
	}
	return root;
}

void del(Tree& root)
{
	Clear(root);
}

void tree_formula(Tree root)
{
	if (root)
	{
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << '(';
		tree_formula(root->left);
		std::cout << root->info;
		tree_formula(root->right);
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << ')';
	}
}

using SInfo = Tree;

class stack
{
private:
	SInfo* elements;
	int size;
	int top;
public:
	stack();
	~stack();
	bool empty();
	bool full();
	void resize(int n_size);
	int get_alloc_size();
	void push(SInfo elem);
	SInfo pop();
	int get_top();
	void View();
};

stack::stack()
{
	size = 1;
	elements = new SInfo[size];
	top = -1;
}

stack::~stack()
{
	delete[] elements;
}

bool stack::empty()
{
	return top == -1;
}

bool stack::full()
{
	return top == size - 1;
}

void stack::resize(int n_size)
{
	if (n_size > size)
	{
		SInfo* temp = new SInfo[n_size];
		for (int i = 0; i <= top; i++)
			temp[i] = elements[i];
		size = n_size;
		delete[] elements;
		elements = temp;
	}
}

int stack::get_alloc_size()
{
	return size;
}

void stack::push(SInfo elem)
{
	if (size == top + 1)
		resize(2 * size);
	elements[++top] = elem;
}

SInfo stack::pop()
{
	SInfo elem = elements[top--];
	return elem;
}

int stack::get_top()
{
	return top;
}

void stack::View()
{
	for (int i = top; i >= 0; i--)
		std::cout << elements[i] << ' ';
	std::cout << std::endl;
}