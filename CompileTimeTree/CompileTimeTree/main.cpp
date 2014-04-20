#include "avltree.h"
#include <vector>
#include <ctime>

using namespace::std;

void print_tree(avl * root, char depth)
{
	if (root == nullptr)
	{
		return;
	}
	print_tree(root->r, depth + 1);
	for(int i = 0; i < depth; i++)
		printf("  ");
	printf("%2d\n", root->k);
	print_tree(root->l, depth + 1);
}

avl * test_add(avl * root, int key, vector<int> * v)
{
	v->push_back(key);
	root = add(root, key);
	for(int i = 0; i < v->size(); i++)
	{
		if (!find(root, (*v)[i]))
		{
			printf("fail");
		}
	}
	return root;
}

avl * test_delete(avl * root, int key, vector<int> * v)
{
	v->push_back(key);
	root = remove(root, key);
	for(int i = 0; i < v->size(); i++)
	{
		if (find(root, (*v)[i]))
		{
			printf("fail\n");
		}
	}
	return root;
}


/*
int main()
{




	int z;
	scanf("%d", &z);
	return 0;
}
*/
