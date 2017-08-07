#include<iostream>
#include<gmp.h>

using namespace std;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		cout<<"\nUsage : "<<argv[0]<<" num1 num2 \n";
		return 0;
	}
	mpz_t a, b, temp;
	mpz_init_set_str(a, argv[1], 10);
	mpz_init_set_str(b, argv[2], 10);
	mpz_init(temp);

	if(mpz_cmp(a,b) > 0)	
		mpz_swap(a, b);
	//find gcd
	while(mpz_cmp_ui(a, 0) != 0)
	{
		mpz_mod(temp, b, a);
		mpz_set(b, a);
		mpz_set(a, temp);
	}
	cout<<"\nGCD of "<<argv[1]<<" and "<<argv[2]<<" is "<<mpz_get_str(NULL, 10, b)<<endl;
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(temp);
}
