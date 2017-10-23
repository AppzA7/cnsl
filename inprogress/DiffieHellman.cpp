#include <iostream>
#include <gmpxx.h>
#include "pqgenerator.cpp"
using namespace std;


void genKey(mpz_class&, mpz_class, mpz_class, mpz_class);	//public key, generator, prime, private key

int main()
{
	mpz_class a, b;
	cout << "Enter Alice's private key : ";
	cin >> a;
	cout << "Enter Bob's private key : ";
	cin >> b;

	mpz_class aK, bK, sK1, sK2, q, p;
	q = primitive_generator(p, 512); //using a 512 bit prime
	genKey(aK, q, p, a);	//Alice
	genKey(bK, q, p, b);	//Bob

	//transpose keys step
	//Alice gets Bob's public key and Bob get's Alice's

	genKey(sK1, bK, p, a);	//Alice
	genKey(sK2, aK, p, b);	//Bob

	cout << "\nThe common shared secret key is : " << sK1;

	if(sK1 != sK2)	//this shouldn't happen1
	{
		cout << "\nThe keys are not equal";
	}
	cout << endl;
	
	return 0;
}

void genKey(mpz_class& pubk, mpz_class q, mpz_class p, mpz_class prik)
{
	mpz_powm(pubk.get_mpz_t(), q.get_mpz_t(), prik.get_mpz_t(), p.get_mpz_t());
}