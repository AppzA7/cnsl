#include <iostream>
#include <stdlib.h>

using namespace std;

struct bignum {
	char *byte = NULL;
	int capacity = 0;
	int size = 0;
};

void add(struct bignum &n, int i)
{
	if(n.capacity == 0)
	{
		n.capacity = 2;
		n.size = 0;
		n.byte = new char[n.capacity];
	}
	else if(n.capacity - 1 == n.size)
	{
		n.capacity *= 2;
		char *a = new char[n.capacity];
		for(int i=0;i<n.size;i++)
			a[i] = n.byte[i];
	}
}
void str2bignum(struct bignum &n, string s)
{
	string p;
	int remainder = 0;
	int number;
	while(s != "")
	{
		if(s.length() > 3)
		{
			p = s.substr(s.length() - 3, 3);
			s = s.subst(0, s.length() - 3);
			cout<<"\ns is "<<s<<"\np is "<<p;
		}
		else
			{p = s;cout<<"\np is "<<p;}
		number = atoi(p);
		if(number > 255)
		{
			remainder = number % 255
			number = number / 255;
		}
	}
}
int main() {
	
	string first, second;
	cout<<"Enter the first number : ";
	cin>>first;
	cout<<"Enter the second number : ";
	cin>>second;

}