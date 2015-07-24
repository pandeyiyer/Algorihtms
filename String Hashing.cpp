#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007   // mod -> A Big prime value
#define p 27             // p -> greater than number of distinct charcaters
#define MAXN 250005      // maximum no. of characters
ll power[MAXN],hash1[MAXN],hash2[MAXN];
string s1,s2;

void pre_compute()
{
    ll i,n,m;
    power[0]=1;
    for(i=1;i<=250001;i++)
    {
        power[i]=(power[i-1]*p)%mod;    // power -> It stores the power
    }
    n=s1.size();
    m=s2.size();

    hash1[0]=s1[0]-'a'+1;
    hash2[0]=s2[0]-'a'+1;

    for(i=1;i<n;i++)
    {
        hash1[i]=(hash1[i-1]*p+s1[i]-'a'+1)%mod;  // hash computation of Ist String
    }
    for(i=1;i<m;i++)
    {
        hash2[i]=(hash2[i-1]*p+s2[i]-'a'+1)%mod;  // hash computation of 2nd String
    }
}

ll compute_hash1(ll l,ll r)
{
    if(l==0) return hash1[r]%mod;    // if(l==0) then (l-1)<0 , so return only h[r]
    else
    {
        // first multiply hash[l-1] with power[r-l+1] then minus from hash[r] to follow harner's rule.

        return ((hash1[r]-hash1[l-1]*power[r-l+1]%mod)%mod+mod)%mod;
    }
}

ll compute_hash2(ll l,ll r)
{
    if(l==0) return hash2[r]%mod;
    else
    {
        return ((hash2[r]-hash2[l-1]*power[r-l+1]%mod)%mod+mod)%mod;
    }
}

int main()
{
    cin>>s1>>s2;
    pre_compute();
    ll q;
    cin>>q;
    while(q--)
    {
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<compute_hash1(a,b)%mod<<" "<<compute_hash2(c,d)%mod<<endl;
    }
    return 0;
}
