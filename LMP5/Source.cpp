#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
	root = nullptr;
}

bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;

	}
	if ((word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void print(TrieTree t, std::string word)
{
	if (t->eow)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)

		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

void printall(TrieTree t, std::string word)
{
	bool flag = 1;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			flag = 0;
	if (flag)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			printall(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

int task(TrieTree& t,int *array, int count, int needed)
{
	int result=0;
	int i = 0;
	for (i = 0; i < 26; i++)
	{
		bool flag = false;
		for (int j = 0; j < 6; j++)
		{
			if (i == array[j] - 'a')
				flag = 1;
		}
		if (t->ptrs[i] && flag)
		{
			result += task(t->ptrs[i], array, count+1, needed);
		}
		else if (t->ptrs[i])
			result += task(t->ptrs[i],array,count, needed);
	}
	if (t->eow && count == needed)
		result++;
	return result;
}

int main()
{
	std::ifstream file("input.txt");
	TrieTree root;
	init(root);
	std::string word;
	int array [6] = {97, 101, 105, 111, 117, 121};
	while (std::getline(file, word))
	{
		if (word.length())
			add(root, word, 0);
	}
	file.close();
	print(root, "");

	int n;

	std::cout << "Input number \n";

	std::cin >> n;

	std::cout << task(root,array,0, n) << "\n";

	clear(root);
	std::cin.ignore();
}
