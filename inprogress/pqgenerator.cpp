#ifndef __GMP_PLUSPLUS__
#include <gmpxx.h>
#endif
#ifndef _TIME_H
#include <time.h>
#endif

#include <iostream>
#include <unistd.h>
using namespace std;

mpz_class prime_generator(int bits)
{
	gmp_randclass r1(gmp_randinit_default);
	r1.seed(time(NULL));
	return r1.get_z_bits(bits);
}

mpz_class primitive_generator()
{
	mpz_class p, p1;
	// do{
	// 	p = prime_generator(1024); 	
	// 	p1 = 2*p  + 1;
	// 	int a = mpz_probab_prime_p(p1.get_mpz_t(), 25);
	// 	if( (a == 1) || (a == 2))
	// 		break;
	// 	else
	// 	{
	// 		usleep(100);
	// 		cout << "Hi";
	// 	}
	// }while(1);

	p.set_str("100247586742465659892559723845323896960199833514136456045974804845288813489897927077289354524577368439637385598465750518427313164248229824351288848003261681883064847727925325843187917219691610936376901694227514557511044920779549145127999138596443073435944700358430443487566833387259837390324095854928985222781", 10);
	p1.set_str("200495173484931319785119447690647793920399667028272912091949609690577626979795854154578709049154736879274771196931501036854626328496459648702577696006523363766129695455850651686375834439383221872753803388455029115022089841559098290255998277192886146871889400716860886975133666774519674780648191709857970445563" ,10);
	mpz_class r1, r2, b, two;
	two = 2;
	cout << "\ntwo is "<<two;
	int found = 0;
	// cout << "\nq : " << p;
	// cout << "\n2q+1 : " << p1; 
	for(int i=2;i<=20;i++)
	{
		cerr << "\n---LOOP " << i;
		cout.flush();
		b = i;
		cerr << "\nCheck 1";
		mpz_powm(r1.get_mpz_t(), b.get_mpz_t(), p.get_mpz_t(), p1.get_mpz_t());
		cerr << "\nCheck 2";
		mpz_powm(r2.get_mpz_t(), b.get_mpz_t(), two.get_mpz_t(), p1.get_mpz_t());
		cout << "\nCheck 3";
		if( (r1 != 1)  && (r2 != 1))
		{
			int found = 1;
			break;
		}
	}
	if(found)
	{
		cout << "The generator is : " << b;
	}
}

int main()
{
	cout << "random value : ";
	cout << primitive_generator();
	cout << std::endl;
	return 0;
}