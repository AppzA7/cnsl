#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
typedef basic_string<unsigned char> ustring;

struct bignum {
	unsigned char *byte = NULL;
	int capacity = 0;
	int size = 0;
};

ustring uint2form(unsigned int i)
{
	ustring s = reinterpret_cast<const unsigned char*>("");
	while(i)
	{
		s += i%256;
		i = i/256;
	}
	return s;
}

//its meh
void add(struct bignum &n, unsigned int i)
{
	string s = uint2form(i);
	cout<<"\nstring is "<<s;
	fprintf(stderr, "\nhihi");
	if(s.length() > n.capacity)
	{
		if(!n.capacity)
			n.capacity = 1;
		int factor = s.length()/n.capacity + 1;
		n.capacity *= factor;
		unsigned char *a = new unsigned char[n.capacity];
		for(int i=0;i<n.size;i++)
			a[i] = n.byte[i];
		delete[] n.byte;
		n.byte = a;
	}
	int k;
	unsigned int car = 0;
		
	fprintf(stderr, "\nhihi");
	for(k=0;k<n.size;k++)
	{
		cout<<"\n1-";
		car += s[k] + n.byte[k];
		n.byte[k] = car % 256;
		car = car / 256;
	}
	fprintf(stderr, "\nhihi");
	while(k < s.length())
	{
		cout<<"\n2-";
		car += s[k];
		cout<<"\n Car is "<<(unsigned int)car;
		n.byte[k++] = car % 256;
		car = car / 256;
		n.size++;
	}
	fprintf(stderr, "\nhihi");
	if(car)
	{
		cout<<"\n3-";
		n.byte[k] = car;
		n.size++;
	}
	/*
	if(n.capacity == 0)
	{
		cout<<"\nAllocating";
		n.capacity = 2;
		n.size = 0;
		n.byte = new unsigned char[n.capacity];
	}
	else if(n.capacity - 1 == n.size)
	{
		n.capacity *= 2;
		unsigned char *a = new unsigned char[n.capacity];
		for(int i=0;i<n.size;i++)
			a[i] = n.byte[i];
		delete[] n.byte;
		n.byte = a;
	}

	cout<<"\nSize : "<<n.size<<endl<<"capacity : "<<n.capacity;
	cout<<"\n i is "<<i;
	unsigned int rem;
	unsigned int k = 0;
	 
	do {
		
		if(k < n.size)
		{
			i += n.byte[k];
			cout<<"\nHI\n";
			if( i > 255)
			{
				cout<<"\na22ssignign to "<<k<<" "<<255;
				n.byte[k++] = 255;
				i -= 255;
			}
			else
			{
				cout<<"\na22ssignign to "<<k<<" "<<i;
				n.byte[k++] = (unsigned char)(i);
				break;
			}
		}
		else
		{
			if(i > 255)
			{
				cout<<"\nassignign to "<<k<<" "<<255;
				n.byte[k++] = 255;
				n.size++;
				i -= 255;
			}
			else
			{
				cout<<"\nassignign to "<<k<<" "<<i;
				n.byte[k++] = (unsigned char)(i);
				n.size++;
				break;
			}
		}
	}while(i > 0);
	cout<<"\nDOne";
	cout<<"\n size is "<<n.size;
	*/
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
			s = s.substr(0, s.length() - 3);
			cout<<"\ns is "<<s<<"\np is "<<p;
		}
		else
			{p = s;cout<<"\np is "<<p;}
		number = atoi(p.c_str());
		if(number > 255)
		{
			remainder = number % 255;
			number = number / 255;
		}
	}
}
int main() {
	
	/*string first, second;
	cout<<"Enter the first number : ";
	cin>>first;
	cout<<"Enter the second number : ";
	cin>>second;*/
	struct bignum a;
	a.capacity = 0;
	a.size = 0;
	add(a, 255);
	cout<<endl;
	for(int i=0;i<a.size;i++)
		cout<<(unsigned int)(a.byte[i])<<" ";
	delete[] a.byte;
	cout<<endl;
	return 0;

}