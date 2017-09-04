//Have to do the mod part and multiplication and division and fix the working for negative numbers

#include <bits/stdc++.h>
using namespace std;

#define be(a) a.begin(), a.end()
string add(string a, string b)
{
	string c = "";
	char carry = 0;
	reverse(be(a));
	reverse(be(b));

	int i = a.length();
	int j = b.length();

	int k = 0;
	while(k < (i>j?i:j))
	{
		if(k < i && k < j)
		{
			c = c + char((a[k]-'0' + b[k] - '0' + carry)%10 + '0');
			carry = (a[k]-'0' + b[k] - '0' + carry)/10;	
		}
		else if(k < i)
		{
			c = c + a[k];
		}
		else if(k < j)
		{
			c = c + b[k];
		}
		k++;
	}
	if(carry)
		c = c + char(carry + 48);
	reverse(be(c));
	return c;
}
string sub(string a, string b)
{
	string c = "";
	char flag = 0;
	reverse(be(a));
	reverse(be(b));

	int i = a.length();
	int j = b.length();

	if(a < b)
	{
		flag = 1;
		swap(a,b);
		swap(i, j);
	}

	int k = 0;
	while(k < i)
	{
		if(k < j)
		{
			//cout<<"a[k], b[k] = "<<a[k]<<", "<<b[k]<<", k="<<k<<endl;
			if(a[k] >= b[k])
				c = c + char((a[k] - b[k]) + '0');
			else
			{
				for(int x = k+1;x < i;x++)
				{
					if(!a[x]){
						a[x] = 9;
					}
					else
					{
						a[x]--;
						break;
					}
				}
				c = c + char(a[k] + 10 - b[k] + '0');
			}
		}
		else
		{
			c = c + a[k];
		}
		k++;
	}

	reverse(be(c));
	for(i =0;i<c.length();i++)
	{
		if(c[i]!='0')
			break;
	}
	c = c.substr(i);
	if(flag)
		c = '-' + c;
	return c;
}
string mul(string a, string b)
{

}
string div(string a, string b)
{

}

bool mygreater(string a, string b)
{
	if(a[0] == '-' && b[0] != '-')
		return false;
	if(a[0] != '-' && b[0] == '-')
		return true;
	if(a.length() > b.length())
		return !(a[0] == '-');
	if(a.length() < b.length())
		return (a[0] == '-');
	else
	{
		for(int i=0;i<a.length();i++)
			if(a[i]!=b[i])
				return a[i]>b[i];
	}

}
string mod(string a, string b)
{
	if(mygreater(a, "0"))
	while(mygreater(a, b))
	{
		cout<<"\nGreater";
		a = sub(a,b);
	}
	else if(mygreater("0", a))
	{
		cout<<"\nlesser";
		while(mygreater("0", a))
			a = add(a, b);
	}
	cout<<"\nreturning";
	return a;
}
int main()
{
	string a, b, c;
	cout<<"Enter two numbers (base 10): \n";
	cout<<"1> ";
	cin>>a;
	cout<<"2> ";
	cin>>b;
	cout<<"\nEnter the mod value : ";
	cin>>c;
	cout<<a<<" + "<<b<<" = "<<mod(add(a, b), c)<<endl;
	cout<<a<<" - "<<b<<" = "<<mod(sub(a, b), c)<<endl;
	//cout<<a<<" * "<<b<<" = "<<mod(mul(a, b), c)<<endl;
	//cout<<a<<" / "<<b<<" = "<<mod(div(a, b), c)<<endl;
}