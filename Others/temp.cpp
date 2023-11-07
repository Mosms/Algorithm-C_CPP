#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int T, n, m, e, cnt, tot, ans, hd[N], p[N], match[N], pre[N], vst[N], dfn[N];
queue<int> q;
struct edge
{
    int t, nxt;
} es[N * N];
char ss[1 << 17], *A = ss, *B = ss;
inline char gc() { return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? -1 : *A++; }
inline void read(int &x)
{
    x = 0;
    int s = gc();
    while (!isdigit(s))
        s = gc();
    while (isdigit(s))
        x = (x << 3) + (x << 1) + s - '0', s = gc();
}
void print(int x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
//设置精度的标准方式cout << setiosflags(ios::fixed) << setprecision(1) << distance << endl;