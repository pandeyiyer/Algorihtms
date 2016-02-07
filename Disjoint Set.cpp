#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007
#define si(i) scanf("%lld",&i);
#define pi(i) printf("%lld",i);
#define rep(i,st,end) for(i=st;i<end;i++) 

#define MAXN 100005

ll parent[MAXN],rank[MAXN]; // rank is the height of tree

void create_set(ll x){
	parent[x] = x;
	rank[x] = 0;	
}

ll find_set(ll x){
	if(parent[x] != x) parent[x] = find_set(parent[x]);
	return parent[x]; 
}

void merge_sets(ll x,ll y){
	ll xroot = find_set(x);
	ll yroot = find_set(y);
	if(rank[xroot]<rank[yroot]) parent[xroot] = yroot;
	else if(rank[xroot]>rank[yroot]) parent[yroot] = xroot;
	else{
		parent[xroot] = yroot;
		rank[yroot]++;
	}
}

int main(){
    
    #ifndef ONLINE_JUDGE
    	freopen("in","r",stdin);
    	freopen("out","w",stdout);
	#endif
    
	ll n,k;
	si(n);
	for(ll i=1;i<=n;i++) create_set(i);
	si(k);
	while(k--){
		ll x,y;
		si(x); si(y);
		merge_sets(x,y);
	}
    ll ans = 0;
    for(ll i=1;i<=n;i++){
    	ll x = find_set(i);
    	if(x != i) ans++;
    }
    pi(ans);
    return 0;
}
