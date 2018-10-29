#include <cstdio>

using namespace std;

const int MAXN = 10000;

int tot, seed = 233, rt;

struct fhqTreap {
    int pos[MAXN], w[MAXN], siz[MAXN], son[MAXN][2];
    int Rand() {
        return seed = int(seed * 48271LL % 2147483647);
    }
    void pus(int x) {
        siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
    }
    int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(pos[x] < pos[y]) {
            son[x][1] = merge(son[x][1], y);
            pus(x);
            return x;
        } else {
            son[y][0] = merge(x,son[y][0]);
            pus(y);
            return y;
        }
    }
    void split(int i, int x, int &a, int &b) {
        if (!i) a = 0,b = 0;
        else {
            if (w[i] <= x)
                a = i, split(son[i][1], x, son[i][1], b);
            else 
                b = i, split(son[i][0], x, a, son[i][0]);
            pus(i);
        }
    }
    void ins(int x) {
        int a, b;
        split(rt, x, a, b);
        w[++tot] = x, siz[tot] = 1, pos[tot] = Rand();
        rt = merge(merge(a,tot),b);
    }
    void del(int x) {
        int a, b, c;
        split(rt, x, a, c);
        split(a, x-1, a, b);
        b = merge(son[b][0], son[b][1]);
        rt = merge(merge(a, b), c);
    }
    int rank(int x) {
        int a, b;
        split(rt, x - 1, a, b);
        int ans = siz[a] + 1;
        rt = merge(a, b);
        return ans;
    }
    int mink(int k, int i) {
        int hh = siz[son[i][0]] + 1;
        if (hh == k) return w[i];
        if (hh > k) return mink(k, son[i][0]);
        return mink(k - hh, son[i][1]);
    }
    int pre(int x) {
        int a, b;
        split(rt, x - 1, a, b);
        int ans = mink(siz[a], a);
        rt = merge(a, b);
        return ans;
    }
    int nxt(int x) {
        int a, b;
        split(rt, x, a, b);
        int ans = mink(1, b);
        rt = merge(a, b);
        return ans;
    }
};

int main() {
    fhqTreap T;
    int M;
    scanf("%d", &M);
    for(int i = 1; i <= M; i++) {
        int op, x;
        scanf("%d %d", &op, &x);
        if (op == 1) T.ins(x);
        if (op == 2) T.del(x);
        if (op == 3) printf("%d\n", T.rank(x));
        if (op == 4) printf("%d\n", T.mink(x,rt));
        if (op == 5) printf("%d\n", T.pre(x));
        if (op == 6) printf("%d\n", T.nxt(x));
    }
    return 0;
}