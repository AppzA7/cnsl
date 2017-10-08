#include <iostream>
#include <gmp.h>

using namespace std;

string add(mpz_t a_, mpz_t b_, int deg);
string mul(mpz_t a, mpz_t b, int deg);
string div(mpz_t a, mpz_t b, int deg);
string sub(mpz_t a, mpz_t b, int deg);
string poly(mpz_t a, int deg);

int main(int argc, char **argv)
{
	int deg;
	string a, b;
	cout<<"Degree of polynomial (<=10): ";
	cin>>deg;

	cout<<"The polynomials have to be entered in the following form \n \
		       x^2 + 1 => 101 \n \
		       x^3     => 100 \n";
	cout<<"\nEnter the first polynomial : ";
	cin>>a;
	cout<<"Enter the second polynomial : ";
	cin>>b;

	mpz_t x, y;
	mpz_init(x);
	mpz_init(y);
	mpz_set_str(x, a.c_str(), deg);
	mpz_set_str(y, b.c_str(), deg);

	cout<<"\nThe numbers in mpz are : \n"<<mpz_get_str(NULL, deg, x)<<"\n"<<mpz_get_str(NULL, deg, y)<<endl;

	string (*fp) (mpz_t a, mpz_t b, int deg);
	fp = &add;
	cout<<"\nThe result of "<<poly(x, deg)<<" + "<<poly(y, deg)<<" = "<<fp(x,y, deg);
	//fp = &sub;
	cout<<"\nThe result of "<<poly(x, deg)<<" - "<<poly(y, deg)<<" = "<<fp(x,y, deg);
	//fp = &mul;
	cout<<"\nThe result of "<<poly(x, deg)<<" * "<<poly(y, deg)<<" = "<<fp(x,y, deg);
	//fp = &div;
	cout<<"\nThe result of "<<poly(x, deg)<<" / "<<poly(y, deg)<<" = "<<fp(x,y, deg);
}

string xx = "x^";
string sp = " + ";

string poly(mpz_t a, int deg)
{
	mpz_t t, degree;
	mpz_init(t);
	mpz_init(degree);
	mpz_set(t, a);
	mpz_init_set_str(degree, to_string(deg).c_str(), 10);

	string s = "";
	mpz_t res;
	mpz_init(res);
	int d = 0;
	mpz_mod(res, t, degree);
	while((mpz_cmp_d(t, 0) != 0))
	{
		d++;
		mpz_div(t, t, degree);
		if(mpz_cmp_d(res, 0) != 0)
		if(d!= 1)
		{
			s = xx + std::to_string(d) + sp + s;
			if(mpz_cmp_d(res, 1) != 0)
				s = mpz_get_str(NULL, 10, res) + s;
		}
		else
			s = std::to_string(d);
		mpz_mod(res, t, degree);
	}

	return " (" + s + ") ";
}

string add(mpz_t a_, mpz_t b_, int deg)
{

	string s = "";
	mpz_t a, b, ua, ub, un, degr;
	mpz_init(a);
	mpz_init(b);
	mpz_set(a, a_);
	mpz_set(b, b_);
	mpz_init(degr);
	mpz_init(ua);	//units digit of a;
	mpz_init(ub);	//units digit of b;
	mpz_init(un);
	int d=1;
	mpz_set_ui(degr, deg);

	while((mpz_cmp_d(a, 0) != 0) && (mpz_cmp_d(b, 0) != 0))		//iterate till either one reaches zero
	{
		mpz_mod(ua, a, degr);
		mpz_mod(ub, b, degr);
		mpz_add(un, ua, ub);
		if(mpz_cmp_d(un, 0)!=0)								// if there is some value at the current position
		{
			if(d!=1)
			{
				s = xx + to_string(d) + sp + s;
				if(mpz_cmp_d(un, 1) != 0)
					s = mpz_get_str(NULL, 10, un) + s;
			}
			else
			{
				if(mpz_cmp_d(un, 0) != 0)
					s = "1";
				else
					s = mpz_get_str(NULL, deg, NULL);
			}
		}
		d++;
		mpz_div(a, a, degr);		//reduce the numbers
		mpz_div(b, b, degr);		
	}
	return s;
}
string mul(mpz_t a, mpz_t b, int deg)
{

}
string div(mpz_t a, mpz_t b, int deg)
{

}
string sub(mpz_t a, mpz_t b, int deg)
{

}