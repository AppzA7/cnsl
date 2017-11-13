#include <unistd.h>
#include <bits/stdc++.h>
#include <gmpxx.h>

using namespace std;

int main()
{
	string s;
	gmp_randclass r (gmp_randinit_default);

	mpz_class e,d,n,p,q,phi,cnst=512,g,i1,i2;

	r.seed(time(NULL));
		
	mpz_nextprime(p.get_mpz_t(),(phi = r.get_z_bits(cnst)).get_mpz_t());
	sleep(1);
	mpz_nextprime(q.get_mpz_t(),(phi = r.get_z_bits(cnst)).get_mpz_t());

	n = p*q;
	phi = (p-1)*(q-1);

	while(1)
	{
		e = r.get_z_range(phi);
		if(e>1)
		{
			mpz_gcd(g.get_mpz_t(),e.get_mpz_t(),phi.get_mpz_t());
			if(g==1)
			{
				break;
			}	
		}
	}
	
	mpz_gcdext(g.get_mpz_t(),i1.get_mpz_t(),i2.get_mpz_t(),e.get_mpz_t(),phi.get_mpz_t());

	d = (i1+phi)%phi;

	cout << "\nGenerated pub, pri key pair : (" << e << "\n, " << n << ")" << " , \n" << d; 
	cout<<"\nEnter a message for encryption"<<endl;
	getline(cin,s);
	
	mpz_class m=0,m1=0,a[100]={},temp,mask = 127;
	long long int i=s.length()-1,cnt=0,ccnt=0;
	while(i>=0)
	{
		m1^=s[i];
		ccnt++;
		if(m1>n)
		{
			mpz_powm(g.get_mpz_t(),m.get_mpz_t(),e.get_mpz_t(),n.get_mpz_t());
			a[cnt] = g;
			cnt++;
			m1=s[i],m=0,ccnt=0;
		}
		m = m1;
		m1 *= 128;
		i--;
	}

	//encrypt remaining message ..
	if(m!=0)
	{
		mpz_powm(g.get_mpz_t(),m.get_mpz_t(),e.get_mpz_t(),n.get_mpz_t());
		a[cnt] = g;
		cnt++;
	}
	cout << "\nencrypted message : ";
	for(int i=0;i<cnt;i++)
	{
		cout << a[i];	
	}

	cout << "\nDecrytping message .. \n";
	//decryption ...
	for(int i=0;i<cnt;i++)
	{
		mpz_powm(a[i].get_mpz_t(),a[i].get_mpz_t(),d.get_mpz_t(),n.get_mpz_t());
		while(a[i]!=0)
		{
			cout<<char((temp = (a[i]&mask)).get_ui());
			a[i]/=128;
		}
	}
	
	return 0;
}
