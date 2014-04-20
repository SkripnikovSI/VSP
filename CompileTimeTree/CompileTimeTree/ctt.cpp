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

template <>
struct balance<nil>
{
	typedef nil result;	
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

template <typename avl, int key>
struct find;

template <typename avl, int key, bool flag>
struct find1
{};

template <typename avl, int key>
struct find1<avl, key, true>
{
	static const bool result = true;
};

template <typename avl, int key>
struct find1<avl, key, false>
{
	static const bool result = key < avl::k ? find<avl::l, key>::result : find<avl::r, key>::result;
};

template <typename avl, int key>
struct find
{
	static const bool result = find1<avl,key, avl::k == key>::result;
};

template <int key>
struct find<nil, key>
{
	static const bool result = false;
};

template <typename avl, typename left> 
struct get_min
{
	static const int result = get_min<left, typename left::l>::result;
};

template <typename avl> 
struct get_min<avl, nil>
{
	static const int result = avl::k; 
};

template <typename avl, typename left> 
struct del_min
{
	typedef typename balance<node<avl::k, typename del_min<left, typename left::l>::result, typename avl::r>>::result result;
};

template <typename avl> 
struct del_min<avl, nil>
{
	typedef typename avl::r result;
};

template <typename avl, int key, bool flag>
struct remove1;

template <typename avl, int key>
struct removeq
{
	typedef typename balance<typename remove1<avl, key, (key == avl::k)>::result>::result result;
};

template <int key>
struct removeq<nil, key>
{
	typedef nil result;
};

template <typename avl, int key, typename right>
struct remove21
{
	typedef node<get_min<right, typename right::l>::result, typename avl::l, typename del_min<right, typename right::l>::result> result;
};

template <typename avl, int key>
struct remove21<avl, key, nil>
{
	typedef typename avl::l result;
};

template <typename avl, int key, bool flag>
struct remove22
{};

template <typename avl, int key>
struct remove22<avl, key, true>
{
	typedef node<avl::k, typename removeq<typename avl::l, key>::result, typename avl::r> result;
};

template <typename avl, int key>
struct remove22<avl, key, false>
{
	typedef node<avl::k, typename avl::l, typename removeq<typename avl::r, key>::result> result;
};

template <typename avl, int key, bool flag>
struct remove1
{};

template <typename avl, int key>
struct remove1<avl, key, true>
{
	typedef typename remove21<avl, key, typename avl::r>::result result;
};

template <typename avl, int key>
struct remove1<avl, key, false>
{
	typedef typename remove22<avl, key, (key < avl::k)>::result result;
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
	typedef removeq<tree, 5>::result tree1;
	typedef removeq<tree1, 6>::result tree2;
	typedef removeq<tree2, 4>::result tree3;
	std::cout<<0<<" "<<find<tree3, 0>::result<<"\n";
	std::cout<<1<<" "<<find<tree3, 1>::result<<"\n";
	std::cout<<2<<" "<<find<tree3, 2>::result<<"\n";
	std::cout<<3<<" "<<find<tree3, 3>::result<<"\n";
	std::cout<<4<<" "<<find<tree3, 4>::result<<"\n";
	std::cout<<5<<" "<<find<tree3, 5>::result<<"\n";
	std::cout<<6<<" "<<find<tree3, 6>::result<<"\n";
	std::cout<<7<<" "<<find<tree3, 7>::result<<"\n";
	std::cout<<8<<" "<<find<tree3, 8>::result<<"\n";
	std::cout<<9<<" "<<find<tree3, 9>::result<<"\n";
	std::cout<<10<<" "<<find<tree3, 10>::result<<"\n";
	print_type<tree3>(0);
		int z;
	std::cin>>z;
	return 0;
}

