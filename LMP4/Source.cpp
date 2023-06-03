#include "Tree.h"

void task2(Tree& t)
{
	ptrNODE tmp = t.get_root();
	STACK otlozh;
	STACK oper;
	cout << "__________\n";
	while (tmp)
	{
		if (tmp->right)
		{
			if (tmp->left)
				otlozh.push(tmp->left);
			if (*tmp->info == '+' || *tmp->info == '-' || *tmp->info == '*' || *tmp->info == '^')
				oper.push(tmp);
			tmp = tmp->right;
		}
		else
			if (tmp->left)
			{
				if (*tmp->info == '+' || *tmp->info == '-' || *tmp->info == '*' || *tmp->info == '^')
					oper.push(tmp);
				tmp = tmp->left;
			}
			else
				if (otlozh.empty())
					tmp = nullptr;
				else
					tmp = otlozh.pop();
	}

	ptrNODE root = t.get_root();
	while (!oper.empty())
	{
		ptrNODE ptr = oper.pop();
		if ((*ptr->info == '+' || *ptr->info == '-') && (*ptr->left->info == '0' || *ptr->right->info == '0'))
		{
			if (*ptr->left->info == '+' || *ptr->left->info == '-' || *ptr->left->info == '*' || *ptr->left->info == '^')
			{
				ptrNODE tmp_prev_root = oper.pop();
				if (tmp_prev_root)
				{
					tmp_prev_root->left = ptr->left;
					ptr->right = nullptr;
					ptr->left = nullptr;
					t.del(ptr);
					oper.push(root);
				}
				else
				{
					t.set_root(ptr->left);
					ptr->left = nullptr;
					t.del(ptr);
				}
			}
			else
				if (*ptr->right->info == '+' || *ptr->right->info == '-' || *ptr->right->info == '*' || *ptr->right->info == '^')
				{
					ptrNODE tmp_prev_root = oper.pop();
					if (tmp_prev_root)
					{
						tmp_prev_root->right = ptr->right;
						ptr->right = nullptr;
						ptr->left = nullptr;
						t.del(ptr);
						oper.push(root);
					}
					else
					{
						t.set_root(ptr->right);
						ptr->right = nullptr;
						t.del(ptr);
					}
				}
				else
					if (*ptr->left->info == '0')
					{
						*ptr->info = *ptr->right->info;
						ptr->left = nullptr;
						ptr->right = nullptr;
						delete ptr->left;
						delete ptr->right;
					}
					else
					{
						*ptr->info = *ptr->left->info;
						ptr->left = nullptr;
						ptr->right = nullptr;
						delete ptr->left;
						delete ptr->right;
					}
		}
		else
			if ((*ptr->info == '*') && (*ptr->left->info == '1' || *ptr->right->info == '1'))
			{
				if (*ptr->left->info == '+' || *ptr->left->info == '-' || *ptr->left->info == '*' || *ptr->left->info == '^')
				{
					ptrNODE tmp_prev_root = oper.pop();
					if (tmp_prev_root)
					{
						*tmp_prev_root = *ptr->left;
						ptr->right = nullptr;
						t.del(ptr->right);
					}
					else
					{
						*root = *ptr->left;
						ptr->right = nullptr;
						t.del(ptr->right);
					}
				}
				else
					if (*ptr->right->info == '+' || *ptr->right->info == '-' || *ptr->right->info == '*' || *ptr->right->info == '^')
					{
						ptrNODE tmp_prev_root = oper.pop();
						if (tmp_prev_root)
						{
							tmp_prev_root->right = ptr->right;
							ptr->right = nullptr;
							ptr->left = nullptr;
							t.del(ptr);
							oper.push(root);
						}
						else
						{
							t.set_root(ptr->right);
							if (t.get_root() == ptr)
								cout << "yes\n";
							ptr->right = nullptr;
							t.del(ptr);
						}
					}
					else
						if (*ptr->left->info == '1')
						{
							*ptr->info = *ptr->right->info;
						}
						else
						{
							*ptr->info = *ptr->left->info;
						}
				ptr->left = nullptr;
				ptr->right = nullptr;
				delete ptr->left;
				delete ptr->right;
			}
			else
				if ((*ptr->info == '*') && (*ptr->left->info == '0' || *ptr->right->info == '0'))
				{
					if (*ptr->left->info == '0')
					{
						*ptr->info = *ptr->left->info;
					}
					else
					{
						*ptr->info = *ptr->right->info;
					}
					ptr->left = nullptr;
					ptr->right = nullptr;
					delete ptr->left;
					delete ptr->right;
				}
				else
					if (ptr->left && ptr->right && (*ptr->info == '^') && (*ptr->right->info == '1' || *ptr->right->info == '0' || *ptr->left->info == '1'))
					{
						if (*ptr->right->info == '1')
						{
							*ptr->info = *ptr->left->info;
						}
						else
						{
							*ptr->info = *ptr->left->info;
						}
						ptr->left = nullptr;
						ptr->right = nullptr;
						delete ptr->left;
						delete ptr->right;
					}
	}
}

int main()
{
	Tree t;
	ifstream file;
	file.open("input.txt");
	t.build_formul(file);
	t.print_level();
	cout << '\n';
	t.print_formul();
	cout << '\n';
	task2(t);
	t.print_formul();
	cin.get();
	return 0;
}