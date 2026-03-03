#include<cstdio>
#include<cstring>
#include<iostream>
#define MOD 1000000007
#define N 200000
using namespace std;
int i,j,k,n,T,K,len,m,ax;
long long aa;
char s[N],ans[N];
int main()
{
	scanf("%d",&T);
	for (K=1;K<=T;K++)
	{
		getchar();
		scanf("%s",s);
		len=strlen(s);
		ans[len]='\0';
		if (len%2)
		{
			m=(len)/2;
			ans[0]=s[m];ax=0;
			for (i=1;i<=m;i++)
			{
				if (s[m-i]>s[m+i])
				{
					ans[++ax]=s[m-i];
					ans[++ax]=s[m+i];
				} else
				{
					ans[++ax]=s[m+i];
					ans[++ax]=s[m-i];
				}
			}
		} else
		{
			m=len/2;ax=-1;
			for (i=1;i<=m;i++)
			{
				if (s[m-i]>s[m+i-1])
				{
					ans[++ax]=s[m-i];
					ans[++ax]=s[m+i-1];
				} else
				{
					ans[++ax]=s[m+i-1];
					ans[++ax]=s[m-i];
				}
			}
		}	
		aa=0;
		for (i=0;i<len;i++)
		{
			if (ans[i]=='1') aa=(aa*2+1)%MOD;
			else aa=(aa*2)%MOD;
		}
		printf("Case #%d: %lld\n",K,aa);
			
	}
}