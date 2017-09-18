#include <bits/stdc++.h>

using namespace std;

string encrypt(string pt, string key)
{
	int i=0;
	while(pt.length() >= key.length())
	{
		key = key + key[i++];
	}
	transform(pt.begin(), pt.end(), pt.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	string ct = "";
	i = 0;
	while(i < pt.length())
	{
		ct = ct + char(((pt[i] - 'A' + (key[i]-'A'))%26) + 'A');
		i++;
	}
	return ct;
}
string decrypt(string ct, string key)
{
	transform(ct.begin(), ct.end(), ct.begin(), ::toupper);
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	int i=0;
	string pt = "";
	while(ct.length() >= key.length())
	{
		key = key + key[i++];
	}
	i = 0;
	while(i < ct.length())
	{
		int val;
		if(ct[i] - key[i] < 0)
		{
			val = 26 + (ct[i] - key[i])%26;
		}
		else
			val = (ct[i] - key[i])%26;
		pt = pt + char(val + 'A');
		i++;
	}
	return pt;
}
int main()
{
	do{
	cout<<"\n1 : encrypt \n2 : decrypt \n3 : exit \n : ";
	int a;
	cin>>a;
	if(a == 3)
		break;
	cout<<"Enter key : ";
	string key;
	cin>>key;
	cout<<"enter text : ";
	string text;
	cin>>text;
	if(a == 1)
		cout<<"Ciphertext is "<<encrypt(text, key);
	else
		cout<<"Plaintext is "<<decrypt(text, key);
	}while(1);
	return 0;
}