#include <bits/stdc++.h>
#define N 100001
#define P 1000000007
#define M(x) (((x) + P) % P)
using namespace std;

typedef long long ll;

ll a[N];

struct sum { ll s1, s2; } st[1<<18];
struct tag { ll t1, t2; } tg[1<<18];

sum combine(sum n1, sum n2) {
    return { M(n1.s1 + n2.s1), M(n1.s2 + n2.s2) };
}

void update(int a, int b, int p, int lb, int rb) {
    st[p].s2 = M(M(M(1ll * a * a) * st[p].s2) + M(M(2ll * a * b) * st[p].s1) + M((rb - lb) * M(1ll * b * b)));
    st[p].s1 = M(M(st[p].s1 * a) + M(1ll * (rb - lb) * b));
    tg[p].t1 = M(tg[p].t1 * a);
    tg[p].t2 = M(tg[p].t2 * a + b);
}

void push_down(int p, int lb, int rb) {
    int mid = (lb + rb) >> 1;
    update(tg[p].t1, tg[p].t2, p << 1, lb, mid);
    update(tg[p].t1, tg[p].t2, p << 1 | 1, mid, rb);
    tg[p].t1 = 1; tg[p].t2 = 0;
}

void push_up(int p) {
    st[p] = combine(st[p << 1], st[p << 1 | 1]);
}

void build(int p, int lb, int rb) {
    tg[p].t1 = 1; tg[p].t2 = 0;
    if (lb + 1 == rb) {
        st[p].s1 = a[lb];
        st[p].s2 = M(a[lb] * a[lb]);
    }
    else {
        int mid = (lb + rb) >> 1;
        build(p << 1, lb, mid);
        build(p << 1 | 1, mid, rb);
        push_up(p);
    }
}

void modify(int l, int r, int a, int b, int p, int lb, int rb) {
    if (l <= lb && rb <= r) update(a, b, p, lb, rb);
    else {
        int mid = (lb + rb) >> 1;
        push_down(p, lb, rb);
        if (l < mid) modify(l, r, a, b, p << 1, lb, mid);
        if (r > mid) modify(l, r, a, b, p << 1 | 1, mid, rb);
        push_up(p);
    }
}

sum query(int l, int r, int p, int lb, int rb) {
    if (l <= lb && rb <= r) return st[p];
    else {
        int mid = (lb + rb) >> 1;
        sum res = { 0, 0 };
        push_down(p, lb, rb);
        if (l < mid) res = combine(res, query(l, r, p << 1, lb, mid));
        if (r > mid) res = combine(res, query(l, r, p << 1 | 1, mid, rb));
        return res;
    }
}

int main(void) {
    //ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n + 1);
    while(q--) {
        int o, l, r;
        cin >> o >> l >> r; ++r;
        if (o == 4) {
            sum ress = query(l, r, 1, 1, n + 1);
            ll s0 = r - l;
            ll res = M(M(s0 * ress.s2) - M(ress.s1 * ress.s1));
            cout << res << endl;
        }
        else {
            int k; cin >> k;
            if (o == 1)
                modify(l, r, 1, k, 1, 1, n + 1);
            else if (o == 2)
                modify(l, r, k, 0, 1, 1, n + 1);
            else if (o == 3)
                modify(l, r, 0, k, 1, 1, n + 1);
        }
    }

    return 0;
}

