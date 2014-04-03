#include "stdafx.h"
#include <iostream>

using namespace std;

extern "C" double __cdecl fun(double x, int n);
extern "C" int __cdecl fact(int a);
extern "C" int __cdecl divbyten(int * m);
extern "C" int __cdecl mydiv(int a, int b);
extern "C" void __cdecl print(char * c0, char * c1, char * c2);

void test(char * format, int number) 
{
	char out_buf[100];
	char num[100];
	char form[100];
	sprintf(num,"%d", number);
	sprintf(form,"k%si\n", format);
	form[0] = '%';
	char c2[100];
	print(out_buf, format, num);
	printf("%s\n", out_buf);
	printf(form, number);
}
int main()
{
	int a = 5;
	int b = 0;
	test("", 0);
	test("-", 0);
	test("-5", 0);
	test("+", 0);
	test("05", 0);
	test(" ", 0);
	cin>>a;
}

