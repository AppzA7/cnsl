#include<time.h>
#include<stdio.h>
#include<gmp.h>

#define mgs(a) mpz_get_str(NULL, 10, a)
#define mc(a) mpz_clear(a);
#define mi(a) mpz_init(a);
#define msui(a,b) mpz_set_ui(a,b);
#define ms(a,b) mpz_set(a,b);
void extended_gcd(mpz_t a, mpz_t b)
{
	mpz_t s, old_s, t, old_t, r, old_r, q, tmp, tmp2;
	
	mi(tmp)
	mi(tmp2);
	mi(q)
	mi(s);
	mi(old_s);
	mi(t);
	mi(old_t);
	mi(r);
	mi(old_r);
	
	msui(s, 0);
	msui(t, 1)
	msui(old_s, 1)
	msui(old_t, 0)
	ms(r, b)
	ms(old_r, a)
	while(mpz_cmp_ui(r, 0) != 0)
	{
		mpz_div(q, old_r, r);
		ms(tmp, old_r)
		ms(old_r, r)
		mpz_mul(tmp2, q, r);
		mpz_sub(r, tmp, tmp2);
		ms(tmp, old_s)
		ms(old_s, s)
		mpz_mul(tmp2, q, s);
		mpz_sub(s, tmp, tmp2);
		ms(tmp, old_t)
		ms(old_t, t)
		mpz_mul(tmp2, q, t);
		mpz_sub(t, tmp, tmp2);
	}

	printf("Bezout Coefficients are : %s %s\nGCD : %s\n", mgs(old_s), mgs(old_t), mgs(old_r));
	printf(" => %s*%s + %s*%s = gcd(%s, %s) = %s\n", mgs(a), mgs(old_s), mgs(b), mgs(old_t), mgs(a), mgs(b), mgs(old_r));
	mc(tmp)
	mc(q)
	mc(s);
	mc(old_s);
	mc(t);
	mc(old_t);
	mc(r);
	mc(old_r);	
}
int main(int argc, char **argv)
{
	mpz_t a, b;
	
	mi(a)
	mi(b)	
	gmp_randstate_t r_state;
	int seed = time(NULL);
	gmp_randinit_default(r_state);
	gmp_randseed_ui(r_state, seed);
	mpz_urandomb(a, r_state, 12);
	mpz_urandomb(b, r_state, 12);
	
	printf("a and b are : %s, %s\n", mgs(a), mgs(b));
	extended_gcd(a, b);
	mc(a);
	mc(b);
}
