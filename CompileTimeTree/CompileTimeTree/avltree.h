struct avl
{
	avl * l;
	avl * r;
	char h;
	int k;
	
	avl * balance();
	avl(int key);
	~avl();
private:	
	avl * left_rotation();
	avl * right_rotation();	
};
int get_min(avl * root);
avl * del_min(avl * root);
avl * add(avl * root, int key);
bool find(avl * root, int key);
avl * remove(avl * root, int key);
char get_h(avl * root);

