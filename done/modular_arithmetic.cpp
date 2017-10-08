#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main(int argc, char **argv)
{
	mpz_t a, b, c, m;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(m);
	if(argc < 2)
	{
		gmp_randstate_t r_state;
		int seed = time(NULL);
		gmp_randinit_default(r_state);
		gmp_randseed_ui(r_state, seed);
		mpz_urandomb(a, r_state, 12);
		mpz_urandomb(b, r_state, 12);
	}
	else
	{
		mpz_set_str(a, argv[1], 10);
		mpz_set_str(b, argv[2], 10);
	}
	char aa[10];
	printf("Enter the mod value : ");
	scanf("%s", aa);
	mpz_set_str(m, aa, 10);

	mpz_add(c, a, b);
	mpz_mod(c, c, m);
	printf("%s + %s = %s\n", mpz_get_str(NULL, 10, a), mpz_get_str(NULL, 10, b), ( mpz_get_str(NULL, 10, c)));

	mpz_sub(c, a, b);
	mpz_mod(c, c, m);
	printf("%s - %s = %s\n", mpz_get_str(NULL, 10, a), mpz_get_str(NULL, 10, b), ( mpz_get_str(NULL, 10, c)));

	mpz_mul(c, a, b);
	mpz_mod(c, c, m);
	printf("%s * %s = %s\n", mpz_get_str(NULL, 10, a), mpz_get_str(NULL, 10, b), ( mpz_get_str(NULL, 10, c)));
	
	mpz_div(c, a, b);
	mpz_mod(c, c, m);
	printf("%s / %s = %s\n", mpz_get_str(NULL, 10, a), mpz_get_str(NULL, 10, b), ( mpz_get_str(NULL, 10, c)));
	
	return 0;

}