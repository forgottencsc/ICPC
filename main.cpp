#include <bits/stdc++.h>
#define N 100001
#define P 1000000007
#define M(x) (((x) + P) % P)
using namespace std;

typedef long long ll;

ll a[N], s1[N], s2[N], t1[N], t2[N];

ll inv(ll x) { return x == 1 ? x : M(inv(P % x) * (P - P / x)); }

void update(ll a, ll b, int p, int lb, int rb) {
    s2[p] = M(M(M(a * a) * s2[p]) + M(M(2ll * a * b) * s1[p]) + M((rb - lb) * M(b * b)));
    s1[p] = M(M(s1[p] * a) + M((rb - lb) * b));
    t1[p] = M(t1[p] * a);
    t2[p] = M(t2[p] * a + b);
}

void push_up(int p) {
    s1[p] = M(s1[p << 1] + s1[p << 1 | 1]);
    s2[p] = M(s2[p << 1] + s2[p << 1 | 1]);
}

void build(int p, int lb, int rb) {
    t1[p] = 1; t2[p] = 0;
    if (lb + 1 == rb) {
        s1[p] = a[lb];
        s2[p] = M(a[lb] * a[lb]);
    }
    else {
        int mid = (lb + rb) >> 1;
        build(p << 1, lb, mid);
        build(p << 1 | 1, mid, rb);
        push_up(p);
    }
}

void modify(int l, int r, ll a, ll b, int p, int lb, int rb) {
    if (l <= lb && rb <= r) update(a, b, p, lb, rb);
    else {
        int mid = (lb + rb) >> 1; b = (((a - 1) * t2[p] + b) * inv(t1[p]));
        if (l < mid) modify(l, r, a, b, p << 1, lb, mid);
        if (r > mid) modify(l, r, a, b, p << 1 | 1, mid, rb);
        push_up(p);
    }
}

pair<int, int> pii;
pii combine(pii p1, pii p2) { return { M(p1.first + p2.first), M(p1.second + p2.second) }; }

pii query(int l, int r, int a, int b, int p, int lb, int rb) {
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
    freopen("1.in", "r", stdin);
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
            ll res = M(M((r - l) * ress.s2) - M(ress.s1 * ress.s1));
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
