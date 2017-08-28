#include <iostream>
#include <gmpxx.h>

using namespace std;

int main()
{
	mpz_class a, b, c;
	cout<<"\nArithmetic in GF(2)\n------------------\n";
	cout<<"Enter first number : ";
	cin>>a;
	cout<<"Enter the second number : ";
	cin>>b;
	c = 2;
	cout<<endl<<a<<" + "<<b<<" = "<<(a+b)%c;
	cout<<endl<<a<<" - "<<b<<" = "<<(a-b)%c;
	cout<<endl<<a<<" * "<<b<<" = "<<(a*b)%c;
	cout<<endl<<a<<" / "<<b<<" = "<<(a/b)%c<<endl;
}