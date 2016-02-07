#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007
#define si(i) scanf("%lld",&i);
#define pi(i) printf("%lld",i);
#define rep(i,st,end) for(i=st;i<end;i++) 

#define MAXN 1005

ll n,root;
ll pos[MAXN],visited[MAXN];
vector<ll> v[MAXN];
vector<ll> e,h;

void findroot(){

	ll tmp[1005];
	memset(tmp,0,sizeof(tmp));

	for(ll i=1;i<=n;i++){
		for(ll j=0;j<v[i].size();j++){
			tmp[v[i][j]]=1;
		}
	}

	root=0;
	for(ll i=1;i<=n;i++){
		if(tmp[i]) continue;
		else{
			root=i;
			break;
		}
	}
}

void euler(ll node,ll level){

	for(ll i=0;i<v[node].size();i++){

		if(!visited[v[node][i]]){

			visited[v[node][i]]=1;

			e.push_back(v[node][i]);
			h.push_back(level+1);

			euler(v[node][i],level+1);

			e.push_back(node);
			h.push_back(level);

		}

	}

}

void position(){
	memset(pos,0,sizeof(pos));

	for(ll i=1;i<e.size();i++){
		if(pos[e[i]]==0){
			pos[e[i]]=i;
		}
	}
}

struct st{
	ll height;
	ll position;
}arr[16*MAXN];

ll sz;
st res;

void build(ll node,ll x,ll y){

	if(x>y) return;

	if(x==y){
		arr[node].height = h[x];
		arr[node].position = x;
		return;
	}

	build(2*node,x,(x+y)/2);
	build(2*node+1,1+(x+y)/2,y);

	if(arr[2*node].height<arr[2*node+1].height){
		arr[node].height = arr[2*node].height;
		arr[node].position = arr[2*node].position;
	}else{
		arr[node].height = arr[2*node+1].height;
		arr[node].position = arr[2*node+1].position;
	}

}

void query(ll node,ll x,ll y,ll a ,ll b){

	if(x>y||a>y||b<x) return;

	if(x>=a && y<=b){
		if(arr[node].height<res.height){
			res=arr[node];
		}
		return;
	}

	query(2*node,x,(x+y)/2,a,b);
	query(2*node+1,1+(x+y)/2,y,a,b);

}

int main(){
    
    #ifndef ONLINE_JUDGE
    	freopen("in","r",stdin);
    	freopen("out","w",stdout);
	#endif
    
	ll t,l;
	si(t);
	for(l=1;l<=t;l++){
		printf("Case %lld:\n",l);
		
		for(ll i=0;i<MAXN;i++) v[i].clear();
		e.clear();
		h.clear();

		memset(pos,0,sizeof(pos));
		memset(visited,0,sizeof(visited));
		memset(arr,0,sizeof(arr));

		si(n);
		for(ll i=1;i<=n;i++){
			ll m;
			si(m);
			while(m--){
				ll tmp;
				si(tmp);
				v[i].push_back(tmp);
			}
		}

		findroot();
		
		e.push_back(0);
		h.push_back(0);
		memset(visited,0,sizeof(visited));

		visited[root]=1;
		e.push_back(root);
		h.push_back(1);
		euler(root,1);
/*
		for(ll i=1;i<e.size();i++) cout<<e[i]<<" ";
		cout<<endl;
*/

		position();

//		for(ll i=1;i<=n;i++) cout<<pos[i]<<" ";

		sz = h.size();
		sz--;
		build(1,1,sz);

		ll q;
		si(q);
		while(q--){
			ll a,b,posa,posb;
			si(a); si(b);
			posa = pos[a];
			posb = pos[b];

			if(posa>posb) swap(posa,posb);

			res.height=mod;
			res.position=mod;

			query(1,1,sz,posa,posb);

			printf("%lld\n",e[res.position]);

		}

	}
    return 0;
}
