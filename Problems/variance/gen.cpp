#include <bits/stdc++.h>
#define N 100001
#define P 1000000007
#define M(x) (((x) + P) % P)
using namespace std;

typedef long long ll;

ll a[N];

struct sum { ll s1, s2; } st[1<<18];
struct tag { ll t1, t2; } tg[1<<18];

inline sum combine(sum n1, sum n2) {
    return { M(n1.s1 + n2.s1), M(n1.s2 + n2.s2) };
}

inline void update(int a, int b, int p, int lb, int rb) {
    st[p].s2 = M(M(M(1ll * a * a) * st[p].s2) + M(M(2ll * a * b) * st[p].s1) + M((rb - lb) * M(1ll * b * b)));
    st[p].s1 = M(M(st[p].s1 * a) + M(1ll * (rb - lb) * b));
    tg[p].t1 = M(tg[p].t1 * a);
    tg[p].t2 = M(tg[p].t2 * a + b);
}

inline void push_down(int p, int lb, int rb) {
    int mid = (lb + rb) >> 1;
    update(tg[p].t1, tg[p].t2, p << 1, lb, mid);
    update(tg[p].t1, tg[p].t2, p << 1 | 1, mid, rb);
    tg[p].t1 = 1; tg[p].t2 = 0;
}

inline void push_up(int p) {
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

void test(int id) {
    ifstream cin(to_string(id) + ".in");
    //ifstream ain(to_string(id) + ".out");
    ofstream aout(to_string(id) + ".out");
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n + 1);
    while(q--) {
        int o, l, r;
        cin >> o >> l >> r; ++r;
        if (o == 3) {
            sum ress = query(l, r, 1, 1, n + 1);
            ll s0 = r - l; //, is0 = inv(s0);
            //ll avg = M(is0 * res.s1);
            //ll var = M(M(is0 * res.s2) - M(avg * avg));
            ll res = M(M(s0 * ress.s2) - M(ress.s1 * ress.s1));
            aout << res << endl;
            //ll ans; ain >> ans;
            //assert(res == ans);
        }
        else {
            int k; cin >> k;
            if (o == 1)
                modify(l, r, 1, k, 1, 1, n + 1);
            else if (o == 2)
                modify(l, r, k, 0, 1, 1, n + 1);
            else if (o == 4)
                modify(l, r, 0, k, 1, 1, n + 1);
        }
    }
}

mt19937_64 mt(chrono::high_resolution_clock::now().time_since_epoch().count()*1145141919ull);

void gen(int n, int q, int wmax, int id) {

    ofstream dout(to_string(id) + ".in");
    //ofstream aout(to_string(id) + ".out");

    uniform_int_distribution<int> xd(1, n), ad(1, wmax);

    srand(ad(mt) * time(0));

    dout << n << ' ' << q << endl;

    for (int i = 1; i <= n; ++i) a[i] = ad(mt);

    for (int i = 1; i <= n; ++i) dout << a[i] <<' '; dout << endl;

    for (int i = 1; i <= q; ++i) {
        int l = xd(mt), r = xd(mt), o = (rand() % 3) + 1;
        if (l > r) swap(l, r);
        dout << o << ' ' << l << ' ' << r;
        if (o == 3) {
            dout << endl;
            //ll s1 = 0, s2 = 0;
            //for (int i = l; i <= r; ++i) {
            //    s1 = M(s1 + a[i]);
            //    s2 = M(s2 + a[i] * a[i]);
            //}
            //aout << M(M((r - l + 1) * s2) - M(s1 * s1)) << endl;
        }
        else {
            ll k = ad(mt);
            dout << ' ' << k << endl;
            //if (o == 1) for (int i = l; i <= r; ++i) a[i] = M(a[i] + k);
            //else if(o == 2) for (int i = l; i <= r; ++i) a[i] = M(a[i] * k);
            //else if(o == 3) for (int i = l; i <= r; ++i) a[i] = k;
        }
    }
}

int main(void) {
    for (int i = 2; i <= 6; ++i) gen(10, 10, 10, i);
    for (int i = 7; i <= 11; ++i) gen(1000, 1000, 1000, i);
    for (int i = 12; i <= 21; ++i) gen(100000, 100000, 1000000000, i);

    for (int i = 1; i <= 21; ++i) test(i);
}
