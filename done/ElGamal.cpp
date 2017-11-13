#include <bits/stdc++.h>
#include <gmpxx.h>

using namespace std;

mpz_class convert(string s)
{
	mpz_class ret;

	for(int i=0;i<s.length();i++)
	{
		ret *= 1000;
		ret += s[s.length()-1-i];
	}

	return ret;
}

string convert1(mpz_class m)
{
	unsigned int t;
	mpz_class temp;
	string res;

	while(m!=0)
	{
		char c = char(t = (temp = m%1000).get_ui());
		cout<<c<<" ";
		res += c;
		m /= 1000;
	}

	return res;
}

int main()
{
	mpz_class m,gcd,g,G,x,p,a,b,A,B,H,i=2,p1=2;
	gmp_randclass r (gmp_randinit_default);

	r.seed(time(NULL));

	while(1)
	{
		mpz_nextprime(G.get_mpz_t(),(g=r.get_z_bits(512)).get_mpz_t());
		g = 2*G+1;

		if(mpz_probab_prime_p(g.get_mpz_t(),20) > 0)
		{
			while(1)
			{
				mpz_powm(x.get_mpz_t(),i.get_mpz_t(),p1.get_mpz_t(),g.get_mpz_t());
				mpz_powm(H.get_mpz_t(),i.get_mpz_t(),G.get_mpz_t(),g.get_mpz_t());
				
				if(x!=1 && H!=1)
					break;

				i++;
			}
		
			break;
		}
	}

	cout<<"Prime : "<<g<<endl;

	cout<<"Generator : "<<i<<endl;

	while(a<=2 || a>= g-2)
	{
		a = r.get_z_bits(512);
	}

	cout<<"Private D : "<<a<<endl;
	
	mpz_powm(A.get_mpz_t(),i.get_mpz_t(),a.get_mpz_t(),g.get_mpz_t());	

	cout<<"Value A^d : "<<A<<endl;

	//public key creation and encryption..

	while(a<=2 || a>=g-2)
	{
		b = r.get_z_bits(512);
	}

	string s = "Example Text";

	m = convert(s);

	cout<<s<<" : "<<m<<endl;

	mpz_class ed;
	mpz_powm(ed.get_mpz_t(),A.get_mpz_t(),b.get_mpz_t(),g.get_mpz_t());

	cout<<"ED : "<<ed<<endl;

	mpz_powm(B.get_mpz_t(),i.get_mpz_t(),b.get_mpz_t(),g.get_mpz_t());

	cout<<"Public P : "<<B<<endl;

	mpz_class c = (ed * m)%g;

	cout<<"CIPHER : "<<c<<endl;

	//decryption of ciphertext..

	mpz_class edd;
	mpz_powm(edd.get_mpz_t(),B.get_mpz_t(),a.get_mpz_t(),g.get_mpz_t());

	cout<<"EDD : "<<edd<<endl;

	mpz_class inv1,inv2;
	mpz_gcdext(gcd.get_mpz_t(),inv1.get_mpz_t(),inv2.get_mpz_t(),edd.get_mpz_t(),g.get_mpz_t());

	inv1 = (inv1+g)%g;
	cout<<"INV1 : "<<inv1<<endl;

	mpz_class pl = (c*inv1)%g;

	s = convert1(pl);

	cout<<"Decrypted : "<<s<<endl;

	return 0;
}
