#pragma once
#include <fstream>
#include <iostream>
using namespace std;

using Tinfo = char;

struct NODE
{
public:
	Tinfo* info;
	NODE* left, * right;
	NODE(Tinfo elem, NODE* left = nullptr, NODE* right = nullptr)
	{
		this->info = new Tinfo(elem);
		this->left = left;
		this->right = right;
	}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
		delete info;
	}
};

using ptrNODE = NODE*;

struct Tree
{
private:
	ptrNODE root;

	NODE* balanse(ifstream& file, int count, ptrNODE& root);
	NODE* formul(ifstream& file);
	void deleter(ptrNODE& root);
	void tree_level(ptrNODE& root, int level);
	void tree_formul(ptrNODE& root);
	void simple(ptrNODE& root);
public:
	Tree();
	~Tree();
	ptrNODE get_root() const
	{
		return root;
	}
	void set_root(ptrNODE& root);
	void del(ptrNODE& root);
	void build_balance(ifstream& f);
	void build_formul(ifstream& f);
	void clear();
	void simplify();
	void print_level();
	void print_formul();
};

using TInfo = ptrNODE;

struct Node
{
public:
	TInfo* elem;
	Node* next;
	Node(TInfo elem, Node* next = nullptr)
	{
		this->elem = new TInfo(elem);
		this->next = next;
	}
	~Node()
	{
		next = nullptr;
		delete elem;
	}
};

using ptrNode = Node*;

struct STACK
{
private:
	Node* top;
public:
	STACK();
	~STACK();
	bool empty();
	void push(TInfo elem);
	TInfo pop();
};