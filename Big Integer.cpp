/*
    Author       :  Jan
    Problem Name :  Biginteger Class
    Algorithm    :  Math
    Complexity   :
*/
 
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
 
using namespace std;
 
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
 
#define CLR(a) memset(a,0,sizeof(a))
 
#ifdef ONLINE_JUDGE
#define i64 long long
#else
#define i64 __int64
#endif
 
const int BASE = 1000000000;                /* Any Base which is power of 10 */
const int POWER = 9;                        /* BASE = 10 ^ POWER */
 
class Bigint
{
private:
    int *digits;                            /* Saved Digits */
    int sign;                               /* +1, 0, -1 */
    int length;                             /* Current Length */
 
public:
    /* Constructors */
    Bigint() { (*this) = 0; }
    Bigint(int n) { (*this) = n; }
 
    /* Assignments */
    void operator = (int);
    void operator = (const char*);
    void operator = (string);
 
    /* Comparisons */
    int compare(Bigint);
    bool operator < (Bigint);
    bool operator > (Bigint);
    bool operator == (Bigint);
    bool operator <= (Bigint);
    bool operator >= (Bigint);
    bool operator != (Bigint);
 
    /* Mathematical Operators */
    Bigint operator + (Bigint);
    Bigint operator - (Bigint);
    Bigint operator * (Bigint);
    Bigint operator / (Bigint);
    Bigint operator % (Bigint);
 
    Bigint operator + (int);
    Bigint operator - (int);
    Bigint operator * (int);
    Bigint operator / (int);
    int operator % (int);
 
    void operator += (Bigint);
    void operator -= (Bigint);
    void operator *= (Bigint);
    void operator /= (Bigint);
    void operator %= (Bigint);
 
    void operator += (int);
    void operator -= (int);
    void operator *= (int);
    void operator /= (int);
    void operator %= (int);
 
    Bigint operator ++ ();
    Bigint operator -- ();
    Bigint operator ++ (int);
    Bigint operator -- (int);
 
    /* Mathematical Functions */
    void divide (Bigint,Bigint&,Bigint&);
    Bigint sqrtBigint();
 
    /* Input Output */
    void print();
    void scan();
 
    /* Basic Parts */
    inline int size() { return length; }
    inline int getSign() { return sign; }
    void normalize();
};
 
void Bigint::normalize()
{
    while(length>=1 && !digits[length-1]) length--;
    if(!length) sign=0,length=1;
}
 
void Bigint::scan()
{
    char a[1001];
    scanf("%s",a);
    *this=a;
}
 
void Bigint::print()
{
    if(sign==-1) putchar('-');
    for(int i=length-1;i>=0;i--)
    {
        if(i==length-1)
            printf("%d",digits[i]);
        else
        {
            char *a;
            a = new char[POWER+1];
            sprintf(a,"%d",digits[i]);
            for(int j=strlen(a);j<POWER;j++) putchar('0');
            printf("%s",a);
        }
    }
    puts("");
}
 
void Bigint::operator = (int n)
{
    if(!n)
    {
        digits=new int[1];
        sign=digits[0]=0;
        length=1;
    }
    else
    {
        sign = (n<0) ? -1 : 1;
        n*=sign;
        length=0;
        digits = new int[(int(log10(double(n))+1e-11)+POWER)/POWER];
        while(n) { digits[length++]=n%BASE; n/=BASE; }
    }
}
 
void Bigint::operator = (const char *a)
{
    int i,j,k,sum,len;
    len=strlen(a);
    if(a[0]=='-') sign=-1,k=1;
    else sign=1,k=0;
    digits = new int[(len-k+POWER-1)/POWER];
    length=0;
    for(i=len-1;i>=k;i-=POWER)
    {
        for(j=max(i-POWER+1,k),sum=0;j<=i;j++) sum=sum*10+a[j]-48;
        digits[length++]=sum;
    }
    if(length==1 && digits[0]==0) sign=0;
}
 
void Bigint::operator = (string a)
{
    int i,j,k,sum;
    if(a[0]=='-') sign=-1,k=1;
    else sign=1,k=0;
    digits = new int[(a.size()-k+POWER-1)/POWER];
    length=0;
    for(i=a.size()-1;i>=k;i-=POWER)
    {
        for(j=max(i-POWER+1,k),sum=0;j<=i;j++) sum=sum*10+a[j]-48;
        digits[length++]=sum;
    }
    if(length==1 && digits[0]==0) sign=0;
}
 
void Bigint::operator += (Bigint n) { (*this) = (*this) + n; }
void Bigint::operator -= (Bigint n) { (*this) = (*this) - n; }
void Bigint::operator *= (Bigint n) { (*this) = (*this) * n; }
void Bigint::operator /= (Bigint n) { (*this) = (*this) / n; }
void Bigint::operator %= (Bigint n) { (*this) = (*this) % n; }
 
void Bigint::operator += (int n) { (*this) = (*this) + n; }
void Bigint::operator -= (int n) { (*this) = (*this) - n; }
void Bigint::operator *= (int n) { (*this) = (*this) * n; }
void Bigint::operator /= (int n) { (*this) = (*this) / n; }
void Bigint::operator %= (int n) { (*this) = (*this) % n; }
 
Bigint Bigint::operator ++ () { (*this) += 1; return (*this); }
Bigint Bigint::operator -- () { (*this) -= 1; return (*this); }
 
Bigint Bigint::operator ++ (int) { Bigint x=(*this); (*this) += 1; return x; }
Bigint Bigint::operator -- (int) { Bigint x=(*this); (*this) -= 1; return x; }
 
int Bigint::compare(Bigint n)
{
    if(sign < n.sign) return -1;
    if(sign > n.sign) return 1;
    if(length < n.length) return -sign;
    if(length > n.length) return sign;
    for(int i=length-1;i>=0;i--)
    {
        if(digits[i] < n.digits[i]) return -sign;
        else if(digits[i] > n.digits[i]) return sign;
    }
    return 0;
}
 
bool Bigint::operator <  (Bigint n){ return( compare(n) < 0 ); }
bool Bigint::operator >  (Bigint n){ return( compare(n) > 0 ); }
bool Bigint::operator == (Bigint n){ return( compare(n) == 0 ); }
bool Bigint::operator <= (Bigint n){ return( compare(n) <= 0 ); }
bool Bigint::operator >= (Bigint n){ return( compare(n) >= 0 ); }
bool Bigint::operator != (Bigint n){ return( compare(n) != 0 ); }
 
Bigint Bigint::operator + (Bigint n)
{
    if(!sign) return n;
    if(!n.sign) return (*this);
    if(sign!=n.sign) { n.sign=-n.sign; return (*this) - n; }
    int i,k,carry;
    Bigint res;
    res.digits = new int[max(length,n.length)+1];
    k=min(length,n.length);
    for(i=carry=0;i<k;i++)
    {
        res.digits[i]=digits[i]+n.digits[i]+carry;
        carry=res.digits[i]/BASE;
        res.digits[i]%=BASE;
    }
    while(i<length)
    {
        res.digits[i]=digits[i]+carry;
        carry=res.digits[i]/BASE;
        res.digits[i++]%=BASE;
    }
    while(i<n.length)
    {
        res.digits[i]=n.digits[i]+carry;
        carry=res.digits[i]/BASE;
        res.digits[i++]%=BASE;
    }
    if(carry) res.digits[i++]=carry;
    res.length=i; res.sign=sign;
    return res;
}
 
Bigint Bigint::operator + (int n)
{
    if(!sign) return n;
    if(!n) return (*this);
    if(sign*n<0) return (*this)-(-n);
    Bigint res;
    int i;
    i64 carry;
    n*=sign;
    res.digits = new int[length+1];
    carry=digits[0]+n;
    res.digits[0]=carry%BASE;
    carry/=BASE;
    for(i=1;i<length;i++)
    {
        carry=carry+digits[i];
        res.digits[i]=carry%BASE;
        carry/=BASE;
    }
    if(carry) res.digits[i++]=carry;
    res.length=i;
    res.sign=sign;
    return res;
}
 
Bigint Bigint::operator - (Bigint n)
{
    if(!sign) { n.sign=-n.sign; return n; }
    if(!n.sign) return (*this);
    if(sign!=n.sign) { n.sign=-n.sign; return (*this) + n; }
    int i,borrow;
    i=sign;
    sign=n.sign=1;
    if((*this) < n) { sign=n.sign=i; n=n-(*this); n.sign=-n.sign; return n; }
    sign=n.sign=i;
    Bigint res;
    res.digits = new int[max(length,n.length)];
    for(i=borrow=0;i<n.length;i++)
    {
        if(digits[i]>=n.digits[i]+borrow)
        {
            res.digits[i]=digits[i]-(n.digits[i]+borrow);
            borrow=0;
        }
        else { res.digits[i]=BASE-(n.digits[i]+borrow)+digits[i]; borrow=1; }
    }
    while(i<length)
    {
        if(digits[i]>=borrow) { res.digits[i]=digits[i]-borrow; borrow=0; }
        else { res.digits[i]=BASE-borrow+digits[i]; borrow=1; }
        i++;
    }
    res.length=i; res.sign=sign; res.normalize();
    return res;
}
 
Bigint Bigint::operator - (int n) // should update
{
    if(!sign) return -n;
    if(!n) return (*this);
    if(sign*n<0) return (*this)+(-n);
    Bigint res;
    int i;
    i64 borrow;
    i=sign;
    sign=1,n*=i;
    if((*this) < n) { sign=i; res=Bigint(n*sign)-(*this); res.sign*=-1; return res; }
    sign=i;
    res.digits = new int[length];
    borrow=digits[0]-n;
    if(borrow<0) { res.digits[0]=borrow+BASE; borrow=1; }
    else { res.digits[0]=borrow; borrow=0; }
    for(i=1;i<length;i++)
    {
        borrow=digits[i]-borrow;
        if(borrow<0) { res.digits[i]=borrow+BASE; borrow=1; }
        else { res.digits[i]=borrow; borrow=0; }
    }
    res.length=i;
    res.sign=sign;
    res.normalize();
    return res;
}
 
Bigint Bigint::operator * (Bigint n)
{
    if(!sign) return (*this);
    if(!n.sign) return n;
    int i,j;
    i64 carry;
    Bigint res;
    res.digits = new int[length+n.length];
    memset(res.digits,0,sizeof(int)*(length+n.length));
    for(i=0;i<length;i++)
    {
        for(carry=j=0;j<n.length;j++)
        {
            carry=carry+digits[i]*(i64)n.digits[j]+res.digits[i+j];
            res.digits[i+j]=carry%BASE;
            carry/=BASE;
        }
        carry=carry+res.digits[i+j];
        res.digits[i+j]=carry%BASE;
    }
    res.length=length+n.length;
    res.sign=sign*n.sign;
    res.normalize();
    return res;
}
 
Bigint Bigint::operator * (int n)
{
    if(n==0 || !sign) return 0;
    int i;
    i64 carry;
    Bigint res;
    res.sign=(n<0 ? -1 : 1) * sign;
    if(n<0) n*=-1;
    res.digits = new int[ (int(log10(double(n))+1e-11)+POWER)/POWER + length ];
    for(carry=i=0;i<length;i++)
    {
        carry=carry+digits[i]*(i64)n;
        res.digits[i]=carry%BASE;
        carry/=BASE;
    }
    while(carry)
    {
        res.digits[i++]=carry%BASE;
        carry/=BASE;
    }
    res.length=i;
    return res;
}
 
Bigint Bigint::operator / (Bigint n)
{
    Bigint quotient,reminder;
    divide(n,quotient,reminder);
    return quotient;
}
 
Bigint Bigint::operator / (int n)
{
    if(!n) n/=n;                            /* Division by 0 */
    if(!sign) return (*this);
    i64 rem=0;
    Bigint res;
    res.sign=(n<0 ? -1 : 1) * sign;
    if(n<0) n*=-1;
    res.digits = new int[length];
    for(int i=length-1;i>=0;i--)
    {
        rem=rem*BASE+digits[i];
        res.digits[i]=rem/n;
        rem%=n;
    }
    res.length=length;
    res.normalize();
    return res;
}
 
Bigint Bigint::operator % (Bigint n)
{
    Bigint quotient,reminder;
    divide(n,quotient,reminder);
    return reminder;
}
 
int Bigint::operator % (int n)
{
    if(!n) n/=n;                            /* Division by 0 */
    if(!sign) return 0;
    i64 rem=0,k;
    k=(n<0 ? -1 : 1) * sign;
    if(n<0) n*=-1;
    for(int i=length-1;i>=0;i--) rem=(rem*BASE+digits[i])%n;
    if(k==-1) rem=(n-rem)%n;
    return int(rem);
}
 
/*
    The Division Algorithm:
 
    STEP  1: If there is no element left then goto STEP 10
    STEP  2: dividend = divdend * BASE + current element
    STEP  3:    k=1;
    STEP  4:    if(k=0) goto STEP 9
    STEP  5:    X = divisor ^ k
    STEP  6:    if X is less than or equal to dividend, dividend -= X and k *= 2
    STEP  7:    else k /= 2
    STEP  8:    goto STEP 4
    STEP  9: goto STEP 1
    STEP 10: end
*/
 
void Bigint::divide(Bigint n,Bigint &quotient,Bigint &reminder)
{
    if(!n.sign) n.sign/=n.sign;             /* Division by 0 */
    if(!sign) { reminder=quotient=(*this); return; }
    int mx=1,k;
    Bigint sv[32];
    sv[1]=n; sv[1].sign=1;
    quotient.digits = new int[length];
    reminder=0;
    for(int i=length-1;i>=0;i--)
    {
        reminder*=BASE;
        reminder+=digits[i];
        quotient.digits[i]=0;
        k=1;
        while(k)
        {
            if(k>mx) { sv[k]=sv[k-1]+sv[k-1]; mx=k; }
            if(reminder >= sv[k])
            {
                reminder-=sv[k];
                quotient.digits[i]+=(1<<(k-1));
                k++;
            }
            else k--;
        }
    }
    quotient.length=length;
    quotient.sign=sign*n.sign;
    quotient.normalize();
    reminder.sign=n.sign*sign;
    reminder.normalize();
    k=n.sign;
    n.sign=1;
    if(reminder.sign==-1) reminder+=n;
    if(k==-1 && reminder.sign) reminder=n-reminder;
}
 
/*
    The sqrt Algorithm:
 
    STEP 1: Bring up the decimal point.
    STEP 2: From the decimal point to the left and right, pair off the digits by drawing a
            line over each pair of numbers. (These pairs act as a single digit for calculating.)
            If a single digit is to the left, draw a line over it. If a single digit is to the
            right, add a zero and draw a line over both digits.
    STEP 3: Starting at the left most, lined number, take the closest square root and put it
            in the answer.
    STEP 4: Square it and subtract from the lined number.
    STEP 5: Double the answer and leave a one's digit space. Bring down the next lined pair.
    STEP 6: Divide the doubled answer plus the answer digit into the number brought down.
            (From here on this is just like division.) Subtract the result.
    STEP 7: Repeat STEP 5 and STEP 6 above until the remainder is zero or the desired number
            of decimal places are achieved.
 
    To speed up a bit, used the division algorithm for the division part
*/
 
Bigint Bigint::sqrtBigint()
{
    if(!sign) return (*this);
    if(sign<0) sqrt(-1.0);              /* sqrt(negative number) */
    Bigint res,rem,sv[32];
    i64 x,d;
    int i,k,mx;
    if(length&1) x=digits[length-1],i=length-2;
    else x=(i64)digits[length-1]*BASE+digits[length-2],i=length-3;
    k=int(sqrt(double(x))+1e-11);
    x-=k*(i64)k;
    res=k;
    rem=int(x);
    for(;i>=0;i-=2)
    {
        rem*=BASE; rem+=digits[i]; rem*=BASE; rem+=digits[i-1];
        mx=1;
        sv[1]=(res+res)*BASE;
        k=1;
        d=0;
        while(k)
        {
            d+=(1<<(k-1));
            if(k>mx) { sv[k]=sv[k-1]+sv[k-1]; mx=k; }
            if( rem >= sv[k] + Bigint(d)*d ) rem-=sv[k],k++;
            else d-=(1<<(k-1)),k--;
        }
        rem-=(Bigint(d)*d);
        res=res*BASE+d;
    }
    return res;
}
 
#define MAX 35
 
int n,k;
bool st[MAX][MAX][MAX];
Bigint sv[MAX][MAX][MAX];
 
Bigint call(int r,int c,int k)
{
    if(k>min(r,c)) return 0;
    if(!k) return 1;
    if(st[r][c][k]) return sv[r][c][k];
    st[r][c][k]=true;
    sv[r][c][k]=call(r-1,c-1,k-1)*c+call(r-1,c,k);
    return sv[r][c][k];
}
 
int main()
{
    freopen("b.in","w",stdout);
    //freopen("b1.ans","w",stdout);
 
    int i;
    Bigint X;
 
    X=1;
    for(i=1;i<=17;i++) X*=10;
    for(n=1;n<=30;n++)
    {
        for(k=0;k<=n+1;k++)
        {
            if(call(n,n,k)<X)
            {
                printf("%d %d\n",n,k);
                //call(n,n,k).print();
            }
        }
    }
    puts("0 0");
    return 0;
}
