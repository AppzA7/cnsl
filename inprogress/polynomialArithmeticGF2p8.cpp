#include <iostream>
#include <gmpxx.h>

using namespace std;

inline mpz_class rs(mpz_class a, int count = 1, int base=2)	//right shift
{
	while(count--)
		a = a/base;
	return a;
}
inline mpz_class ls(mpz_class a, int count = 1, int base=2)	//left shift
{
	while(count--)
		a = a*base;
	return a;
}

string print_pretty(mpz_class a)		//only for base 2
{
	string s = a.get_str(2);
	//cout<<"\nInd . "<<s<<" . "<<a;
	if(s.length() == 0)
		return "";
	string out_s = ")";
	int pow = 1;
	if(s[s.length()-1] == '1')
		out_s = "1" + out_s;
	s = s.substr(0, s.length()-1);
	//cout<<"\nInd out_s : "<<out_s;
	for(int i=s.length()-1;i>=0;i--)
	{
		//cout<<"\nInd. for loop iter "<<i;
		if(s[i] == '1')
		{
			out_s = "x" + (pow!=1?("^" + std::to_string(pow)):"") + (out_s != ")"?"+":"") + out_s;
		}
		pow++;
	}
	if(out_s == ")")
		return "0";
	return "(" + out_s;
}

string print_pretty(mpz_class *a)
{
	return print_pretty(*a);
}

mpz_class mod(mpz_class a, mpz_class b)
{
	mpz_class *x, *y;
		x = &a;
		y = &b;
	if(mpz_sizeinbase(x->get_mpz_t(), 2) < mpz_sizeinbase(y->get_mpz_t(), 2))		//the number cant be divided further
		return a;

	mpz_class p, one, zero;
	p.set_str("0", 2);
	one.set_str("1", 2);
	zero.set_str("0", 2);
	mpz_class res;
	res.set_str("0", 2);

	while(mpz_sizeinbase(x->get_mpz_t(), 2) >= mpz_sizeinbase(y->get_mpz_t(), 2))
	{
		*x = *x ^ (ls(*y, mpz_sizeinbase(x->get_mpz_t(), 2) - mpz_sizeinbase(y->get_mpz_t(), 2)));
	}
	return *x;
}
mpz_class mul(mpz_class a, mpz_class b)
{
	mpz_class *x, *y;	//x is the smaller one
	if(a < b)
	{
		x = &a;
		y = &b;
	}
	else
	{
		x = &b;
		y = &a;
	}

	mpz_class p, one, zero;
	p.set_str("0", 2);
	one.set_str("1", 2);
	zero.set_str("0", 2);
	while((*x) != zero) 
	{
		if(((*x)&one) == one)
		{
			p = p^(*y);
		}
		*y = ls(*y);
		*x = rs(*x);
	}

	return p;
}

mpz_class div(mpz_class a, mpz_class b)
{
	mpz_class *x, *y;
		x = &a;
		y = &b;
	if(mpz_sizeinbase(x->get_mpz_t(), 2) < mpz_sizeinbase(y->get_mpz_t(), 2))		//the number cant be divided further
		return a;

	mpz_class p, one, zero;
	p.set_str("0", 2);
	one.set_str("1", 2);
	zero.set_str("0", 2);
	mpz_class res;
	res.set_str("0", 2);

	while(mpz_sizeinbase(x->get_mpz_t(), 2) >= mpz_sizeinbase(y->get_mpz_t(), 2))
	{
		res = res ^ (1<<(mpz_sizeinbase(x->get_mpz_t(), 2) - mpz_sizeinbase(y->get_mpz_t(), 2)));
		*x = *x ^ (ls(*y, mpz_sizeinbase(x->get_mpz_t(), 2) - mpz_sizeinbase(y->get_mpz_t(), 2)));

	}
	return res;
}
int main()
{
	mpz_class a,b,m;
	string input_s;
	cout<<"Polynomial Arithmetic in GF(2^8)\n--------------------------------\n";
	cout<<"Enter the coefficients of the Polynomial in the following form\n";
	cout<<"x^2 + 1 => 101\n";
	cout<<"X^5 + x => 100010\n";
	cout<<"================================\n";
	m.set_str("100011011", 2);	//x^8 + x^4 + x^3 + x + 1
	cout<<"m(x) = "<<print_pretty(m)<<endl;
	int f;
	do{
		cout<<"Enter the first polynomial : ";
		cin>>input_s;
		f = a.set_str(input_s.c_str(), 2);
	}while(f == -1);

	do{
		cout<<f<<"Enter the second polynomial : ";
		cin>>input_s;
		f = b.set_str(input_s.c_str(), 2);
	}while(f == -1);

	cout<<endl<<print_pretty(a)<<" + "<<print_pretty(b)<<" = "<<print_pretty(a^b);
	cout<<endl<<print_pretty(a)<<" - "<<print_pretty(b)<<" = "<<print_pretty(a^b);
	cout<<endl<<print_pretty(a)<<" * "<<print_pretty(b)<<" = "<<print_pretty(mul(a,b));
	cout<<endl<<print_pretty(a)<<" / "<<print_pretty(b)<<" = "<<print_pretty(div(a,b));	

	cout<<endl<<"=================================================================";
	cout<<endl<<print_pretty(a)<<" + "<<print_pretty(b)<<" mod "<<print_pretty(m)<<"="<<print_pretty(a^b);
	cout<<endl<<print_pretty(a)<<" - "<<print_pretty(b)<<" mod "<<print_pretty(m)<<"="<<print_pretty(a^b);
	cout<<endl<<print_pretty(a)<<" * "<<print_pretty(b)<<" mod "<<print_pretty(m)<<"="<<print_pretty(mod(mul(a,b), m));
	cout<<endl<<print_pretty(a)<<" / "<<print_pretty(b)<<" mod "<<print_pretty(m)<<"="<<print_pretty(mod(div(a,b), m));


	cout<<endl;
	return 0;
}