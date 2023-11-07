#include <cstdio>
#include <vector>
#include <cmath>

typedef long long ll;
const ll inf = 1e18;

struct Node {
    int l, r;
    ll res, tag, tag2, res2;
    // tag：当前标记；tag2：历史标记
    // res：当前最小；res2：历史最小
};

class SegmentTree {
    std::vector<Node> a;

    void tag_init(int i) {
        a[i].tag = a[i].tag2 = 0;
    }

    void tag_union(int fa, int i) {
        if (a[fa].tag2 < 0) {
            a[i].tag2 = std::min(a[i].tag2, a[i].tag + a[fa].tag2);
        }
        a[i].tag += a[fa].tag;
    }

    void tag_cal(int i) {
        if (a[i].tag2 < 0) {
            a[i].res2 = std::min(a[i].res2, a[i].res + a[i].tag2);
        }
        a[i].res += a[i].tag;
    }

    void pushdown(int i) {
        tag_cal(i);
        if (a[i].l != a[i].r) {
            tag_union(i, i * 2);
            tag_union(i, i * 2 + 1);
        }
        tag_init(i);
    }

    void pushup(int i) {
        if (a[i].l == a[i].r) return;
        pushdown(i * 2);
        pushdown(i * 2 + 1);
        a[i].res = std::min(a[i * 2].res, a[i * 2 + 1].res);
    }

    void build(int i, int l, int r) {
        a[i].l = l, a[i].r = r;
        tag_init(i);
        if (l >= r) return;
        int mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
    }

public:
    // 区间+w
    void update(int i, int l, int r, ll w) {
        if (a[i].r < l || a[i].l > r || l > r) return;
        pushdown(i);
        if (a[i].l >= l && a[i].r <= r) {
            a[i].tag += w;
            a[i].tag2 = std::min(a[i].tag2, a[i].tag);
            return;
        }
        update(i * 2, l, r, w);
        update(i * 2 + 1, l, r, w);
        pushup(i);
    }

    // 查询历史区间最小
    ll query(int i, int l, int r) {
        pushdown(i);
        if (a[i].r < l || a[i].l > r || l > r) return inf;
        if (a[i].l >= l && a[i].r <= r) {
            return a[i].res2;
        }
        return std::min(query(i * 2, l, r), query(i * 2 + 1, l, r));
    }

    SegmentTree(int n) : a(n * 4) { build(1, 1, n); }
};

int main(void)
{
    return 0;
}