#include "Tree.h"

void task1(Tree& root)
{
	if (root->right && root->left)
	{
		task1(root->right);
		task1(root->left);
		if (root->info == '+' || root->info == '-')
		{
			if (root->right->info == '0')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
			else if (root->left->info == '0')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
		}
		else if (root->info == '*')
		{
			if (root->right->info == '0' || root->left->info == '0')
			{
				root->info = '0';
				Clear(root->left);
				Clear(root->right);
			}
			else if (root->left->info == '1')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
			else if (root->right->info == '1')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
		}
		else if (root->info == '^')
		{
			if (root->right->info == '0' || root->left->info == '0')
			{
				root->info = '1';
				Clear(root->left);
				Clear(root->right);
			}
			else if (root->left->info == '1')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
			else if (root->right->info == '1')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
		}
	}
}

void task2(Tree& p)
{
	Tree root = p;
	stack st;
	stack oper;

	//пока есть дерево влево, то в стек заносится правое поддерево
	//если в корне хранится арифметический знак, сохраняем корень
	//обходим все дерево, потом снизу вверх переходим на корни с арифметическими знаками и делаем проверку

	while (root)
	{
		if (root->left)
		{
			if (root->right)
			{
				st.push(root->right);
			}
			if (root->info == '+' || root->info == '-' || root->info == '*' || root->info == '^')
				oper.push(root);
			root = root->left;
		}
		else if (root->right)
		{
			if (root->info == '+' || root->info == '-' || root->info == '*' || root->info == '^')
				oper.push(root);
			root = root->right;
		}
		else if (st.empty())
			root = nullptr;
		else
			root = st.pop();
	}
	while (!oper.empty())
	{
		root = oper.pop();
		std::cout << '\n';
		Print(root);
		std::cout << '\n';
		tree_formula(root);
		if (root->info == '+' || root->info == '-')
		{
			if (root->right->info == '0')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
			else if (root->left->info == '0')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
			std::cout << '\n';
			Print(root);
		}
		else if (root->info == '*')
		{
			if (root->right->info == '0' || root->left->info == '0')
			{
				root->info = '0';
				Clear(root->left);
				Clear(root->right);
			}
			else if (root->left->info == '1')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
			else if (root->right->info == '1')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
			std::cout << '\n';
			Print(root);
		}
		else if (root->info == '^')
		{
			if (root->right->info == '0' || root->left->info == '0')
			{
				root->info = '1';
				Clear(root->left);
				Clear(root->right);
			}
			else if (root->left->info == '1')
			{
				Clear(root->left);
				Tree ptr = root->right;
				root = ptr;
			}
			else if (root->right->info == '1')
			{
				Clear(root->right);
				Tree ptr = root->left;
				root = ptr;
			}
			std::cout << '\n';
			Print(root);
		}
	}
}

void main()
{
	std::ifstream file("form.txt");
	Tree root;
	root = Build_Formula(file);
	Print(root);

	tree_formula(root);
	std::cout << '\n';
	task2(root);
	tree_formula(root);

	Clear(root);
	std::cin.get();

}


