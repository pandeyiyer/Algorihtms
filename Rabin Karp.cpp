/*    RABIN KARP ALGORITHM

    -> Rabin Karp Algorithm matches the hash value of pattern to hash value of substring of text sliding by one.
    -> here, we find the hash value of each substring by sliding by one in O(1) time.
    -> When the hash value Matches we compare the each character of pattern to text.
    -> In Average Case it runs in O(n+m) time and O(n*m) in worst case.
    -> here, we take prime numbers which treats given numbers in its base.
*/

#include <bits/stdc++.h>
using namespace std;

#define d 256 // no. of different characters
#define q 101 // Prime number

string text,pat;

void rabinkarp()
{
    int m,n,p,t,h,i,j;
    m=pat.size();
    n=text.size();

    p=0; // hash value for pattern
    t=0; // hash value for text
    h=1;

    // h contains pow(d,m-1)%q

    for(i=0;i<m-1;i++)
    {
        h=(h*d)%q;
    }

    // compute hash value for pattern and text

    for(i=0;i<m;i++)
    {
        p=(d*p+pat[i])%q;   // current hash value= ((no. of diff. chars)*(previous hash value)+current pattern)%mod
        t=(d*t+text[i])%q;
    }

    for(i=0;i<=(n-m);i++)
    {
        if(t==p)
        {
            for(j=0;j<m;j++)
            {
                if(pat[j]!=text[i+j]) break;
            }
            if(j==m)
            {
                cout<<"Pattern found at index: "<<i<<endl;
            }
        }

        if(i<n-m)
        {
            t=(d*(t-text[i]*h)+text[i+m])%q;   // current hash value= ((no. of diff. chars)*(previous hash value)+current pattern)%mod
            if(t<0) t+=q;
        }
    }
}


int main()
{
    cin>>text>>pat;
    rabinkarp();
    return 0;
}
