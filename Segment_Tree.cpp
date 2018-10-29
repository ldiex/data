#include<cstdio>
#include<cstring>

using namespace std;

typedef long long LL;

const int MAXN = 1e5 + 5;

LL n, m, a[MAXN];

struct segTree {
    segTree *ls, *rs;
    LL tag, sum, l, r;
    segTree(LL l, LL r, segTree *ls, segTree *rs) :
        l(l), r(r), ls(ls), rs(rs), sum(ls->sum + rs->sum), tag(0) {}
    segTree(LL l, LL r, segTree *ls, segTree *rs, LL sum) :
        l(l), r(r), ls(ls), rs(rs), sum(sum), tag(0) {}
    void pushUp() {
        sum = ls->sum + rs->sum;
    }
    void cover(LL val) {
        tag += val;
        sum += val * (r - l + 1);
    }
    void pushDown() {
        ls->cover(tag);
        rs->cover(tag);
        tag = 0;
    }
    void modify(LL l, LL r, LL val) {
        if (l > this->r || r < this->l) return;
        if (l <= this->l && this->r <= r) 
            cover(val);
        else {
            pushDown();
            ls->modify(l, r, val);
            rs->modify(l, r, val);
            pushUp();
        }
    }
    LL query(LL l, LL r) {
        if (l > this->r || r < this->l) return 0;
        if (l <= this->l && this->r <= r) return sum;
        pushDown();
        return ls->query(l, r) + rs->query(l, r);
    }
    static segTree *build(LL l, LL r) {
        if (l > r) return NULL;
        if (l == r) return new segTree(l, r, NULL, NULL, a[l]);
        LL mid = (l + r) >> 1;
        return new segTree(l, r, build(l, mid), build(mid + 1, r));
    }
}*root;

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) 
        scanf("%lld", &a[i]);
    root = segTree::build(1, n);
    for (int i = 1; i <= m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            LL l, r, k;
            scanf("%lld%lld%lld", &l, &r, &k);
            root->modify(l, r, k);
        } else {
            LL l, r;
            scanf("%lld%lld", &l, &r);
            printf("%lld\n", root->query(l, r));
        }
    }
    return 0;
}