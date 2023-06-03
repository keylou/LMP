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

void main()
{
	std::ifstream file("form.txt");
	Tree root;
	root = Build_Formula(file);
	Print(root);

	tree_formula(root);
	std::cout << '\n';
	task1(root);
	tree_formula(root);

	Clear(root);
	std::cin.get();

}


