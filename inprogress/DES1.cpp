#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <fstream>
#include <errno.h>
#include "tables.h"

using namespace std;

char ipa[64] = { 
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 54, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7
};

char ipia[64] = {
40, 8, 48, 16, 56, 24, 64, 32,
39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30,
37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28,
35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26,
33, 1, 41, 9, 49, 17, 57, 25
};

char ea[48] = {
32, 1, 2, 3, 4, 5,
4, 5, 6, 7, 8, 9,
8, 9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1
};

char pa[32] = {
16, 7, 20, 21,
29, 12, 28, 17,
1, 15, 23, 26,
5, 18, 31, 10,
2, 8, 24, 14,
32, 27, 3, 9,
19, 13, 30, 6,
22, 11, 4, 25
};

char pc1[56] = {
57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10, 2, 59, 51, 43, 35, 27,
19, 11, 3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14, 6, 61, 53, 45, 37, 29,
21, 13, 5, 28, 20, 12, 4
};

char pc2[48] = {
14, 17, 11, 24, 1, 5,
3, 28, 15, 6, 21, 10,
23, 19, 12, 4, 26, 8,
16, 7, 27, 20, 13, 2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32
};

uint64_t key = 0x133457799BBCDFF1;//0xFFFFFFFFFFFFFFFF;//0xF987A123BAAD9121;

///	1334 5779 9BBC DFF1
void printbin(uint64_t a)
{
	cout<< "a is " << a << endl;
	for(int i=0;i<64;i++)
	{
		cout << setw(2) << i << " "; 
	}
	cout << endl;
	for(int i=0;i<64;i++)
	{
		cout << setw(2) << ((a&((uint64_t)1<<(63-i)))?1:0) << " "; 
	}

}
void prnb(uint64_t a, char ignore_leading_zero=1, int bits = 64, int space_count = 64)
{
	// cout << dec 	<< "\n printing " << bits << " bits";
	if(space_count == 64)		//just to pretty print the binary values;
		space_count = bits;
	int k = 0;
	if(bits > 64 || bits < 0)
		bits = 64;
	cout << endl;
	int i = 0;
	if(ignore_leading_zero && a != 0)
		while((a & ((uint64_t)1<<(63-i))) == 0)i++;
	for(;i<bits;i++)
	{
		if( k++ % space_count == 0)
			cout << " ";
		cout << ((a&((uint64_t)1<<(63-i)))?1:0); 
	}
}
uint64_t fpc(uint64_t key, int id)
{
	char *pc = id==1?pc1:pc2;
	uint64_t res = 0;
	for(int i=0;i<(pc == pc1 ? 56 : 48);i++)
	{
		res |= ( ( key & ( (uint64_t)1 << (64-pc[i]) ) )?1:0);
		res <<= 1;
	}
	res <<= (63 - (pc == pc1 ? 56 : 48));
	return res;
}

uint64_t keys[16] = {0};	//16 keys  required

void lrotate(uint64_t &val, char l, char r, char cnt)	//l and r are the msb and lsb respectively of the rotated area. 1 -> LSB. right most bit
{
	// cout<< "\n l, r, cnt = "<<(int)l<<", "<<(int)r<<", "<<(int)cnt;
	int rv;
	rv = (val & ((uint64_t)1 << (64-l)))?1:0;
	// cout<<"\n rv = " << rv;
	uint64_t mask;
	
	mask = ((uint64_t)1 << (64-l)) - ((uint64_t)1 << (64-r));
	mask += ((uint64_t)1 << (64-l));

	// cout<<"\n mask = "<< hex << mask;
	cout <<dec;
	// prnb(mask, 0);
	// cout << "\n val before : ";
	// prnb(val,0);
	while(cnt--)
	{
		rv = (val & ((uint64_t)1 << (64-l)))?1:0;
		// cout<<"\n Rotating";
		val <<= 1;
		val &= mask;
		val |= (rv==1?(((uint64_t)1 << (64-r))):0);
	}
	// cout << "\n val after : ";
	// prnb(val, 0);
}

void make_keys()
{
	uint64_t pc1v = fpc(key, 1);	//do pc1 on key
	uint64_t l=0, r=0;
	uint64_t left_mask = 0xFFFFFFF000000000;
	uint64_t right_mask = 0x0000000FFFFFFF00;

	// cout << "\nPC1 = ";
	// prnb(pc1v);
	char shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	for(int i=0;i<16;i++)
	{
		//compute key[i]
		l = pc1v & left_mask;
		r = pc1v & right_mask;
		lrotate(l, 1, 28, shifts[i]);
		lrotate(r, 29, 56, shifts[i]);
		// DEBUG
		// cout << "C and D [" << i + 1 << "]";
		// prnb(l, 0, 28);
		// prnb(r<<28, 0, 28); 
		keys[i] = l | r;
		pc1v = keys[i];
		
		// DO PC2
		keys[i] = fpc(keys[i], 2);
		keys[i] &= 0xFFFFFFFFFFFF0000; 	//TAKE ONLY FIRST 48 BITS
		// cout << "\n key "<< i;
		// prnb(l, 0);
		// prnb(r, 0);
		// prnb(keys[i], 0, 48, 6);
	}
}

uint64_t fip(uint64_t m)
{
	// prnb(m, 0, 64, 4);
	uint64_t c = 0;
	for(int i=0;i<64;i++)
	{
		//prnb(c, 1, 64, 4);
		c <<= 1;
		// cout << "\nreplacing bit " << i + 1 << " with bit " << ((m & ((uint64_t)1 << (64 - ipa[i])))?1:0) << " from " << dec << (int)ipa[i]; 
		c |= ((m & ((uint64_t)1 << (64 - ipa[i])))?1:0);
	}
	return c;
}

uint64_t subs(uint64_t m, char a[], int sizeofa)	//helper function used to permute and substitute. can replace fip and fpc with some modification
{
	// prnb(m, 0, 64, 4);
	uint64_t c = 0;
	for(int i=0;i<sizeofa;i++)
	{
		//prnb(c, 1, 64, 4);
		c <<= 1;
		c |= ((m & ((uint64_t)1 << (64 - a[i])))?1:0);
	}
	return c << (64 - sizeofa);
}

uint64_t s(char i, char row, char col)			//substitution function
{
	char (*sa)[16];
	switch(i)
	{
		case 1: sa = s1;break;
		case 2: sa = s2;break;
		case 3: sa = s3;break;
		case 4: sa = s4;break;
		case 5: sa = s5;break;
		case 6: sa = s6;break;
		case 7: sa = s7;break;
		case 8: sa = s8;break;
	}
	// cout << "\nS "<< (int)i << " returning : "<< (uint64_t)sa[a>>62][(a&0x3C00000000000000)>>58];
	// return (uint64_t)sa[a>>62][(a&0x3C00000000000000)>>58];
	// cout << "\nS "<< (int)i << " returning : "<< (uint64_t)sa[(int)row][(int)col];
	return (uint64_t)sa[(int)row][(int)col];
}

#define GETROW(a, i) ((((a & 0x8000000000000000 >> i*6)?1:0)<<1) + (uint64_t)((a & 0x0400000000000000 >> i*6)?1:0) )
#define GETCOL(a, i) ((a & 0x7800000000000000 >> i*6) >> (59 - i*6))

uint64_t f(uint64_t r, uint64_t key)			//round function
{
	// cout << "\n Inside F";
	uint64_t newr = subs(r, ea, 48);
	// cout << "\nKey";
	// prnb(key, 0, 48, 6);
	newr ^= key;
	// cout << "\nkey + newr";
 // 	prnb(newr, 0, 48, 6);
 	uint64_t result = 0;
 	uint64_t lmask = 0xFC00000000000000;
 	for(int i=0;i<8;i++)
 	{
 		// cout << "\nfor ";
 		// prnb(((lmask & newr) << i), 0, 6, 6);
 		// // cout << "\ncolumn  :" << GETCOL(newr, i);
 		// cout << "\nrow :" << GETROW(newr, i);
 		// cout << "\nsubs is ";
 		// prnb(s( i + 1, GETROW(newr, i), GETCOL(newr, i)) << 60, 0, 4, 6);
 		result |= ( s( i + 1, GETROW(newr, i), GETCOL(newr, i)) << (60 - i*4) );
 		lmask >>= 6;
 	}
 	// cout << "\n after S ";
 	// prnb(result, 0, 32, 4);
 	result = subs(result, pa, 32);
 	// cout << "\n after P ";
 	// prnb(result, 0, 32, 4);
 	return result;
}

uint64_t encrypt(uint64_t m)
{
	// prnb(fip(m), 0, 64, 4);
	uint64_t left_mask = 0xFFFFFFFF00000000;
	uint64_t right_mask = 0x00000000FFFFFFFF;
	uint64_t l, r, ipv, ln, rn;
	ipv = fip(m);
	l = ipv & left_mask;
	r = ipv & right_mask;
	r <<= 32;
	// cout << "\n m value : ";
	// prnb(m, 0, 64, 8);
	// cout << "\nStarting with : ";
	// prnb(ipv, 0, 64, 8);
	for(int i=0 ; i<16 ; i++)	//16 rounds
	{
		ln = r;
		rn = l ^ f(r, keys[i]);
		l = ln;
		r = rn;
		cout << "\n Round : " << i + 1;
		if(i%2 == 1)
		{
			prnb(((l>>32) | r), 0, 64, 8);
		}
		else
		{
			prnb(((r>>32) | r), 0, 64, 8);
		}
		cout << "\nKey";
		prnb(keys[i], 0, 48, 8);

	}
	// cout << "\n l16 and r16";
	// prnb(l, 0, 32, 4);
	// prnb(r, 0, 32, 4);
	uint64_t result = ( (l>>32) | r);
	// cout << "\nbefore ip-1 ";
	// prnb(result, 0, 64, 8);
	// // do inverse permutation on result
	result = subs(result, ipia, 64);
	cout << "\nresult is ";
	prnb(result, 0, 64, 8);
	return result;
}

uint64_t decrypt(uint64_t c)
{
	uint64_t left_mask = 0xFFFFFFFF00000000;
	uint64_t right_mask = 0x00000000FFFFFFFF;
	uint64_t l, r, ln, rn, ipv;
	ipv = fip(c);
	l = ipv & left_mask;
	r = ipv & right_mask;
	
	// cout << "\nc value : ";
	// prnb(c, 0, 64, 8);
	// cout << "\n starting with : ";
	// prnb(ipv, 0, 64, 8);
	
	for(int i=0 ; i<16 ; i++)	//16 rounds
	{
		ln = r;
		cout << "\nUsing key " << 15-i;
		rn = l ^ f(r, keys[15-i]);
		l = ln;
		r = rn;
		cout << "\n Round : " << i + 1;
		if(i%2 == 1)
		{
			prnb(((l>>32) | r), 0, 64, 8);
		}
		else
		{
			prnb(((r>>32) | r), 0, 64, 8);
		}
		cout << "\nKey";
		prnb(keys[15-i], 0, 48, 8);
	}
	cout << "\n l16 and r16";
	prnb(l, 0, 32, 4);
	prnb(r, 0, 32, 4);
	uint64_t result = ( (l>>32) | r);
	prnb(result, 0, 64, 8);
	// do inverse permutation on result
	result = subs(result, ipia, 64);
	return result;
}
int main()
{
	// ifstream infile;
	// ofstream outfile;

	// cout << "Enter the path of the file to encrypt : ";
	// string path;
	// getline(cin, path);
	// cout << "Plaintext path : " << path;
	// infile.open(path.c_str(), ios::binary | ios::in);			//check if this file exists

 // 	infile.seekg(0, ios::end);
 // 	if(infile.tellg() == -1)
 // 	{
 // 		return 0;
 // 	}
 // 	cout << "\n Plaintext size : " << infile.tellg();


	make_keys();	//keys[16] has the 48 bit keys
	cout << "\nThe keys are : ";
	for(int i=0;i<16;i++)
		{
			cout << "\nKey :"<<i;
			prnb(keys[i], 0, 32, 8);
		}
	uint64_t m = 0b0000000100100011010001010110011110001001101010111100110111101111;
	uint64_t c = 0x85e813540f0ab405;
	prnb(m, 0,64,8);
	// uint64_t r = subs(m, ipia, 64);
	// prnb(r, 0,64,8);
	// r = subs(r, ipa, 64);
	// r = fip(r);
	// prnb(r, 0,64,8);
	//prnb(encrypt(m), 0, 64, 8);
	//cout << hex << endl << encrypt(m);
	// cout << endl;
	m = 0XF;
	uint64_t cc = encrypt(m);
	cout << "\nthe encrypted value is " << hex << cc;
	cout << "\nThe decrypted value is " << hex << decrypt(cc);
	return 0;
}	
