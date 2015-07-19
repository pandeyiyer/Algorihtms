// Problem - NHAY on SPOJ

#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n,m,lps[5000001];
string a,b;

void computelps()
{
    ll i,len;
    lps[0]=0;
    i=1;
    len=0;
    while(i<n)
    {
        if(a[i]==a[len])
        {
            len++;
            lps[i]=len;
            i++;
        }
        else
        {
            if(len!=0) len=lps[len-1];
            else
            {
                lps[i]=0;
                i++;
            }
        }

    }
}

void searchstr()
{
    m=b.size();
    ll i,j,cnt;
    i=j=cnt=0;
    while(i<m)
    {
        if(a[j]==b[i])
        {
            i++;
            j++;
        }

        if(j==n)
        {
            cnt++;
            printf("%lld\n",i-j);
            j=lps[j-1];
        }

        if(i<m&&a[j]!=b[i])
        {
            if(j!=0) j=lps[j-1];
            else i++;
        }
    }
    if(cnt==0) printf("\n");
}


int main()
{
    while(scanf("%lld",&n)!=EOF)
    {
        cin>>a>>b;
        computelps();
        searchstr();
    }
    return 0;
}
