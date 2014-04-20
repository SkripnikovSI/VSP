#include "avltree.h"

#define max(a, b) a > b ? a : b

avl::avl(int key)
{
	k = key;
	h = 1;
	l = nullptr;
	r = nullptr;
}

avl::~avl()
{
	delete l;
	delete r;
}

avl * add(avl * root, int key) 
{
	if (root == nullptr)
	{
		return new avl(key);
	}
	if (key < root->k)
	{
		root->l = add(root->l, key);
	}
	else 
	{
		root->r = add(root->r, key);
	}
	return root->balance();
}

bool find(avl * root, int key) 
{
	if (root == nullptr)
	{
		return false;
	}
	if (key == root->k)
	{
		return true;
	}
	return key < root->k ? find(root->l, key) : find(root->r, key);
}

avl * remove(avl * root, int key)
{
	if (root != nullptr)
	{
		if (key == root->k)
		{
			if (root->r != nullptr)
			{
				root->k = get_min(root->r);
				root->r = del_min(root->r);
			}
			else 
			{
				avl * garbage = root;
				root = root->l;
				garbage->l = nullptr;
				delete garbage;
			}
		}
		else if (key < root->k)
		{
			root->l = remove(root->l, key);
		}
		else 
		{
			root->r = remove(root->r, key);
		}
		if (root != nullptr)
		{
			root = root->balance();
		}
	}		
	return root;	
}

avl * del_min(avl * root)
{
	if (root->l != nullptr)
	{
		root->l = del_min(root->l);
		root = root->balance();
	}
	else
	{
		avl * garbage = root;
		root = root->r;
		garbage->r = nullptr;
		delete garbage;
	}
	return root;
}

int get_min(avl * root)
{
	if (root->l != nullptr)
	{
		return get_min(root->l);
	}
	return root->k;
}

avl * avl::left_rotation()
{
    avl * root = r;
	r = r->l;
	root->l = this;
	h = max(get_h(l), get_h(r)) + 1;
	root->h = max(get_h(root->l), get_h(root->r)) + 1;
    return root;
}

avl * avl::right_rotation()
{
    avl * root = l;
	l = l->r;
	root->r = this;
	h = max(get_h(l), get_h(r)) + 1;
	root->h = max(get_h(root->l), get_h(root->r)) + 1;
    return root;
}

avl * avl::balance()
{
	h = max(get_h(l), get_h(r)) + 1;
	if (get_h(l) - get_h(r) == 2)
	{
		if (get_h(l->r) > get_h(l->l))
		{
			l = l->left_rotation();
		}
		return right_rotation();

	}
	else if (get_h(r) - get_h(l) == 2)
	{
		if (get_h(r->l) > get_h(r->r))
		{
			r = r->right_rotation();
		}
		return left_rotation();
	}
	return this;
}

char get_h(avl * root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return root->h;
}
