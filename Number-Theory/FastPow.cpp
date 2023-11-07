#include <cstdio>
#include <cmath>

typedef long long lint;
lint FastPow(lint base, lint exp, lint mod)
{
    lint ans = 1;
    base %= mod;
    while (exp)
    {
        if (exp & 1)
            ans = ans * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

int main(void)
{
    lint a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld\n", FastPow(a, b, c));
    return 0;
}