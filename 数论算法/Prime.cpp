#include <cstdio>
#include <cmath>
#include <cstdint>

const int Maxn = 2000 + 100;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;


ll qmul(ll a,ll b,ll mod)//快速乘
{
    ll c=(ld)a/mod*b;
    ll res=(ull)a*b-(ull)c*mod;
    return (res+mod)%mod;
}
ll qpow(ll a,ll n,ll mod)//快速幂
{
    ll res=1;
    while(n)
    {
        if(n&1) res=qmul(res,a,mod);
        a=qmul(a,a,mod);
        n>>=1;
    }
    return res;
}
bool MRtest(ll n)//Miller Rabin Test
{
    if(n<3||n%2==0) return n==2;//特判
    ll u=n-1,t=0;
    while(u%2==0) u/=2,++t;
    ll ud[]={2,325,9375,28178,450775,9780504,1795265022};
    for(ll a:ud)
    {
        ll v=qpow(a,u,n);
        if(v==1||v==n-1||v==0) continue;
        for(int j=1;j<=t;j++)
        {
            v=qmul(v,v,n);
            if(v==n-1&&j!=t){v=1;break;}//出现一个n-1，后面都是1，直接跳出
            if(v==1) return 0;//这里代表前面没有出现n-1这个解，二次检验失败
        }
        if(v!=1) return 0;//Fermat检验
    }
    return 1;
}

ll Pollard_Rho(ll N)
{
    if (N == 4)
        return 2;
    if (is_prime(N))
        return N;
    while (1)
    {
        ll c = randint(1, N - 1);
        auto f = [=](ll x) { return ((lll)x * x + c) % N; };
        ll t = 0, r = 0, p = 1, q;
        do
        {
            for (int i = 0; i < 128; ++i) // 令固定距离C=128
            {
                t = f(t), r = f(f(r));
                if (t == r || (q = (lll)p * abs(t - r) % N) == 0) // 如果发现环，或者积即将为0，退出
                    break;
                p = q;
            }
            ll d = gcd(p, N);
            if (d > 1)
                return d;
        } while (t != r);
    }
}