#include "Tree.h"

Tree::Tree()
{
	root = nullptr;
}

Tree::~Tree()
{
	deleter(root);
}

void Tree::set_root(ptrNODE& root)
{
	this->root = root;
}

void Tree::del(ptrNODE& root)
{
	deleter(root);
}

void Tree::build_balance(ifstream& f)
{
	int count;
	f >> count;
	root = balanse(f, count, root);
}

void Tree::build_formul(ifstream& f)
{
	root = formul(f);
}

void Tree::clear()
{
	deleter(root);
}

void Tree::simplify()
{
	simple(root);
}

void Tree::print_level()
{
	tree_level(root, 0);
}

void Tree::print_formul()
{
	tree_formul(root);
}

NODE* Tree::balanse(ifstream& file, int count, ptrNODE& root)
{
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		char x;
		file >> x;
		root = new NODE(x);
		root->left = balanse(file, count_left, root->left);
		root->right = balanse(file, count_right, root->right);
	}
	return root;
}

NODE* Tree::formul(ifstream& file)
{
	char c = file.get();
	ptrNODE root = new NODE(' ');
	if ((c >= '0' && c <= '9') || c == 'x' || c == 'y' || c == 'z')
		*root->info = c;
	else
	{
		root->left = formul(file);
		*root->info = file.get();
		root->right = formul(file);
		c = file.get();
	}
	return root;
}

void Tree::deleter(ptrNODE& tmp)
{
	if (tmp)
	{
		deleter(tmp->left);
		deleter(tmp->right);
		delete tmp;
	}
}

void Tree::tree_level(ptrNODE& root, int level)
{
	if (root)
	{
		tree_level(root->right, level + 1);
		for (int i = 0; i < level; ++i)
			cout << "||||||||||";
		cout << *root->info << '\n';
		tree_level(root->left, level + 1);
	}
}

void Tree::tree_formul(ptrNODE& root)
{
	if (root)
	{
		if (!((*root->info >= '0' && *root->info <= '9') ||
			*root->info == 'x' || *root->info == 'y' || *root->info == 'z'))
			cout << '(';
		tree_formul(root->left);
		cout << *root->info;
		tree_formul(root->right);
		if (!((*root->info >= '0' && *root->info <= '9') ||
			*root->info == 'x' || *root->info == 'y' || *root->info == 'z'))
			cout << ')';
	}
}

void Tree::simple(ptrNODE& root)
{
	if (root->left && root->right)
	{
		bool f = false;
		simple(root->left);
		simple(root->right);
		if ((*root->info == '+' || *root->info == '-') && (*root->left->info == '0' || *root->right->info == '0'))
		{
			ptrNODE tmp = root;
			if (*root->left->info == '0')
			{
				root = root->right;
				tmp->right = nullptr;
			}
			else
			{
				root = root->left;
				tmp->left = nullptr;
			}
			deleter(tmp);
		}
		else
			if ((*root->info == '*') && (*root->left->info == '1' || *root->right->info == '1'))
			{
				ptrNODE tmp = root;
				if (*root->left->info == '1')
				{
					root = root->right;
					tmp->right = nullptr;
				}
				else
				{
					root = root->left;
					tmp->left = nullptr;
				}
				deleter(tmp);
			}
			else
				if ((*root->info == '*') && (*root->left->info == '0' || *root->right->info == '0'))
				{
					ptrNODE tmp = root;
					if (*root->left->info == '0')
					{
						root = root->left;
						tmp->left = nullptr;
					}
					else
					{
						root = root->right;
						tmp->right = nullptr;
					}
					deleter(tmp);
				}
				else
					if ((*root->info == '^') && (*root->right->info == '1' || *root->right->info == '0' || *root->left->info == '1'))
					{
						ptrNODE tmp = root;
						if (*root->right->info == '1')
						{
							root = root->left;
							tmp->left = nullptr;
						}
						else
						{
							root = root->left;
							tmp->left = nullptr;
						}
						deleter(tmp);
					}
	}
}

STACK::STACK()
{
	top = nullptr;
}

STACK::~STACK()
{
	ptrNode tmp = top;
	while (top != nullptr)
	{
		top = tmp->next;
		delete tmp;
		tmp = top;
	}
}

bool STACK::empty()
{
	return top == nullptr;
}

TInfo STACK::pop()
{
	ptrNode tmp = top;
	TInfo info = 0;
	if (top)
	{
		info = *tmp->elem;
		top = top->next;
		delete tmp;
	}
	return info;
}

void STACK::push(TInfo elem)
{
	ptrNode tmp = new Node(elem);
	tmp->next = top;
	top = tmp;
}

