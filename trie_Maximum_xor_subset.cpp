// codechef - SEP15
// problem - REBXOR

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 400005
#define sz 20

ll arr[MAXN],sum1[MAXN],sum2[MAXN];

struct node
{
    ll val;
    struct node *left,*right;
    node() {val=-1; left=NULL; right=NULL;}
};

struct trie
{
    struct node *head;
    trie(){head=new node();}
    void add(ll num)
    {
        ll i,j,k;
        struct node *tmp=this->head;
        for(i=sz-1;i>=0;i--)
        {
            if(num&(1<<i))
            {
                if(tmp->right==NULL) tmp->right=new node();
                tmp=tmp->right;
            }
            else
            {
                if(tmp->left==NULL) tmp->left=new node();
                tmp=tmp->left;
            }
        }
        tmp->val=num;
    }
    ll query(ll num)
    {
        ll i,j,k;
        struct node *tmp=this->head;
        for(i=sz-1;i>=0;i--)
        {
            if(num&(1<<i))
            {
                if(tmp->left!=NULL) tmp=tmp->left;
                else tmp=tmp->right;
            }
            else
            {
                if(tmp->right!=NULL) tmp=tmp->right;
                else tmp=tmp->left;
            }
        }
        return tmp->val;
    }
};

int main()
{
    ll n,i,j,k,pre,ans,mx;
    scanf("%lld",&n);
    for(i=1;i<=n;i++) scanf("%lld",&arr[i]);

    trie t1,t2;

    t1.add(0);
    t2.add(0);

    pre=sum1[0]=sum2[n+1]=0;

    for(i=1;i<=n;i++)
    {
        pre^=arr[i];
        if(i>1) sum1[i]=max(sum1[i-1],pre);
        else sum1[i]=pre;
        t1.add(pre);
        sum1[i]=max(sum1[i-1],max(sum1[i],pre^t1.query(pre)));
    }

    pre=0;

    for(i=n;i>=1;i--)
    {
        pre^=arr[i];
        if(i<n) sum2[i]=max(sum2[i+1],pre);
        else sum2[i]=pre;
        t2.add(pre);
        sum2[i]=max(sum2[i+1],max(sum2[i],pre^t2.query(pre)));
    }

    ans=0;

    for(i=1;i<n;i++) ans=max(ans,sum1[i]+sum2[i+1]);

    printf("%lld",ans);

    return 0;
}
