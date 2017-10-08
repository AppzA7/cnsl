#include <iostream>
#include <vector>
#include <gmp.h>

using namespace std;

class polynomial
{
	mpz_t *coeff;
	int size;
	void init();
	void clear();
public:
	polynomial();
	polynomial(vector<int> v);
	~polynomial();
	/*void add(polynomial a);
	void sub(polynomial a);
	void mul(polynomial a);
	void div(polynomial a);*/
	int getsize();
	mpz_t &operator[](int i);
	polynomial(polynomial &a);
};

void polynomial::init()
{
	coeff = new mpz_t[size];
	for(int i=0;i<size;i++)
	{
		mpz_init(coeff[i]);
		mpz_set_ui(coeff[i], 0);	//needed?
	}
}

void polynomial::clear()
{
	for(int i=0;i<size;i++)
	{
		mpz_clear(coeff[i]);
	}
	delete[] coeff;
}

polynomial::polynomial()
{
	size = -1;
	coeff = NULL;
}
polynomial::polynomial(vector<int> v)
{
	size = v.size();
	init();
	for(int i=0;i<v.size();i++)
	{
		mpz_set_ui(coeff[i], v[i]);
	}
}
polynomial::~polynomial()
{
	for(int i=0;i<size;i++)
	{
		mpz_clear(coeff[i]);
	}
	delete[] coeff;
}

mpz_t &polynomial::operator[](int i)
{
	if(i < size)
		return coeff[i];
}

polynomial::polynomial(polynomial &a)
{
	if(a.getsize()!= -1)
	{
		size = a.getsize();
		init();
		for(int i=0;i<size;i++)
		{
			cerr<<"\nsetting value "<<mpz_get_str(NULL, 10, a[i]);
			mpz_set(coeff[i], a[i]);
		}
	}
}

int polynomial::getsize()
{
	return size;
}

int main()
{
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	polynomial b(a);
	cerr<<"Reached here";
	polynomial c(b);
	//b = c;			//error
	cerr<<"didnt come ehrer";
	cout<<b.getsize()<<" "<<mpz_get_str(NULL, 10, b[0])<<" "<<mpz_get_str(NULL, 10, b[1])<<" "<<mpz_get_str(NULL, 10, b[2])<<endl;
	cout<<c.getsize()<<" "<<mpz_get_str(NULL, 10, c[0])<<" "<<mpz_get_str(NULL, 10, c[1])<<" "<<mpz_get_str(NULL, 10, c[2])<<endl;

}