#include <iostream>
#include <gmpxx.h>

using namespace std;

#define KEYBITS 48
#define MSGBITS 64
#define ROUNDS 16		//for DES

char ipa[] = { 58, 50, 42, 34, 26, 18, 10, 2,
					60, 52, 44, 36, 28, 20, 12, 4,
					62, 54, 46, 38, 30, 22, 14, 6,
					64, 56, 48, 40, 32, 24, 16, 8,
					57, 49, 41, 33, 25, 17, 9, 1,
					59, 51, 43, 35, 27, 19, 11, 3,
					61, 54, 45, 37, 29, 21, 13, 5
					63, 55, 47, 39, 31, 23, 15, 7};
char ipia[] = { 40, 8, 48, 16, 56, 24, 64, 32,
				39, 7, 47, 15, 55, 23, 63, 31,
				38, 6, 46, 14, 54, 22, 62, 30,
				37, 5, 45, 13, 53, 21, 61, 29,
				36, 4, 44, 12, 52, 20, 60, 28,
				35, 3, 43, 11, 51, 19, 59, 27,
				34, 2, 42, 10, 51, 18, 58, 26,
				33, 1, 41, 9, 49, 17, 57, 25}
char ea[]= { 32, 1, 2, 3, 4, 5,
			 4, 5, 6, 7, 8, 9,
			 8, 9, 10, 11, 12, 13,
			 12, 13, 14, 15, 16, 17,
			 16, 17, 18, 19, 20, 21,
			 20, 21, 22, 23, 24, 25,
			 24, 25, 26, 27, 28, 29,
			 28, 29, 30, 31, 32, 1}
char pa[] = {16, 7, 20, 21,
			 29, 12, 28, 17,
			 1, 15, 23, 26,
			 5, 18, 31, 10,
			 2, 8, 24, 14,
			 32, 27, 3, 9,
			 19, 13, 30, 6,
			 22, 11, 4, 25}
char pc1[] = {57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10, 2, 59, 51, 43, 35, 27,
19, 11, 3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14, 6, 61, 53, 45, 38, 29,
21, 13, 5, 28, 20, 12, 4}

char pc2[] = {14, 17, 11, 24, 1, 5,
3, 28, 15, 6, 21, 10,
23, 19, 12, 4, 26, 8,
16, 7, 27, 20, 13, 2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32}

string key; 	//64 bit key
string keys[16];
void pad(char *msg, int size_in_bytes)
{
	for(int i = size_in_bytes;i<MSGBITS/8;i++)
		msg[i] = 0;
}

char *substitute(char *i)	//i is half the size of MSGBITS
{
	char *returnval = (char)malloc(sizeof(char)*(MSGBITS/16));
	//look up the substitution table and replace
	return returnval;
}

char *permute(char *i)
{
	char *returnval = (char)malloc(sizeof(char)*(MSGBITS/16));
	memcpy(returnval, i, sizeof(char)*(MSGBITS/16));
	//permute returnval
	return returnval;
}

char* roundFunction(char *i, char *k)
{
	char *expanded = expand(i);
	//xor k and expanded i
	(*expanded) = (*expanded) ^ (*k)
	//substitute
	char *substituted = substitute(expanded);
	//permute
	char *permuted = permute(substituted);
	
	//free memory
	free(substituted);
	free(expanded);
	return permuted;
}


char *getkey()
{
	//remove parity
	string T = "";
	char temp = 0;
	for(int i=0;i<56;i+=8)
	{
		for(int j=0;j<8;j++)
			temp ^= key[i/8]&1<<(64-pc1[i])
			temp <<= 1;
	}
	char T=[]
	string kl, kr;
	kl = key.substr(0, key.size()/2);
	kr = key.substr(key.size()/2, key.size()/2);
	return 0;
}

void doRounds(char *msg)
{
	char *k;
	char *l, *r;
	l = (char)malloc(sizeof(char)*MSGBITS/16);
	r = (char)malloc(sizeof(char)*MSGBITS/16);
	memcpy(l, msg, sizeof(char)*MSGBITS/16);				//left half
	memcpy(r, msg+(MSGBITS/16), sizeof(char)*MSGBITS/16);	//right half
	
	for(int i=0;i<ROUNDS;i++)
	{
		k = getkey();
		char *newr = roundFunction(r, k);
		(*l) = (*l) ^ (*newr);
		free(newr);
		free(k);
		swap(l, r);
	}
	memcpy(msg, l, sizeof(char)*MSGBITS/16);
	memcpy(msg + sizeof(char)*MSGBITS/16, r, sizeof(char)*MSGBITS/16);
}

void IP(char *msg)
{
	

}
void FP(char *msg)
{

}
void DES(char *msg)
{
	IP(msg);
	doRounds(msg);
	FP(msg);
}