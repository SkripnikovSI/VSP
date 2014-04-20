#include <iostream>

#define max(a, b) a > b ? a : b

struct nil
{
	static const int h = 0;
}; 

template <int key, typename Left,  typename Right>
struct node
{
	static const int k = key;
	typedef Left l;
	typedef Right r;
	static const int h = max(l::h, r::h) + 1;
};

template <typename avl>
struct left_rotation
{
	typedef node<avl::r::k, node<avl::k, typename avl::l, typename avl::r::l>, typename avl::r::r> result;
};

template <typename avl>
struct right_rotation
{
	typedef node<avl::l::k, typename avl::l::l, node<avl::k, typename avl::l::r, typename avl::r>> result;
};

template <typename avl, bool flag>
struct balance21
{};

template <typename avl>
struct balance21<avl, true>
{
	typedef typename left_rotation<typename avl::l>::result result;
};

template <typename avl>
struct balance21<avl, false>
{
	typedef typename avl::l result;
};

template <typename avl, int flag>
struct balance1
{
	typedef avl result;
};

template <typename avl>
struct balance1<avl, 2>
{
		typedef typename balance21<avl, (avl::l::r::h > avl::l::l::h)>::result left;
		typedef typename right_rotation<node<avl::k, left, typename avl::r>>::result result;
};

template <typename avl, bool flag>
struct balance22
{};

template <typename avl>
struct balance22<avl, true>
{
		typedef typename right_rotation<typename avl::r>::result result;
};

template <typename avl>
struct balance22<avl, false>
{
		typedef typename avl::r result;
};
	
template <typename avl>
struct balance1<avl, -2>
{
		typedef typename balance22<avl, (avl::r::l::h > avl::r::r::h)>::result right;
		typedef typename left_rotation<node<avl::k, typename avl::l, right>>::result result;
};

template <typename avl>
struct balance
{
	typedef typename balance1<avl, avl::l::h - avl::r::h>::result result;	
};

template <typename avl, int key>
struct add;

template <typename avl, int key, bool flag>
struct add1
{};

template <typename avl, int key>
struct add1<avl, key, true>
{
	typedef typename node<avl::k, typename add<typename avl::l, key>::result, typename avl::r> result;
};

template <typename avl, int key>
struct add1<avl, key, false>
{
	typedef typename node<avl::k, typename avl::l, typename add<typename avl::r, key>::result> result;
};

template <typename avl, int key>
struct add
{
	typedef typename balance<typename add1<avl, key, (key < avl::k)>::result>::result result;	
};

template <int key>
struct add<nil, key>
{
	typedef node<key, nil, nil> result;	
};

template <typename avl, int i>
struct tree_maker
{
	typedef typename add<typename tree_maker<avl, i - 1>::result, i>::result result;	
};

template <typename avl>
struct tree_maker<avl, 0>
{
	typedef typename add<avl, 0>::result result;		
};


template <typename avl>
void print_type(int depth)
{
	print_type<typename avl::r>(depth + 1);
	for(int i = 0; i < depth; i++)
		std::cout<<"  ";
	std::cout<<avl::k<<"\n";
	print_type<typename avl::l>(depth + 1);
}

template <>
void print_type<nil>(int depth)
{}

int main()
{
	typedef tree_maker<nil, 10>::result tree;
	print_type<tree>(0);
		int z;
	std::cin>>z;
	return 0;
}

/*
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
		root = del_min(root->l);
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
*/