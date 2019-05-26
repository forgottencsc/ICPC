#include <bits/stdc++.h>
#define N 1<<20
#define endl '\n'

using namespace std;

typedef long long ll;

mt19937_64 mt(time(0));

struct st_t { ll s, u, v; } st[N << 1];
ll tg[N << 1];

st_t combine(st_t s1, st_t s2) {
    return { s1.s + s2.s, max(s1.u, s2.u), min(s1.v, s2.v) };
}

void update(int t, int p, int lb, int rb) {
    st[p].s += 1ll * t * (rb - lb);
    st[p].u += t;
    st[p].v += t;
    tg[p] += t;
}

void push_down(int p, int lb, int rb) {
    int mid = (lb + rb) >> 1;
    update(tg[p], p << 1, lb, mid);
    update(tg[p], p << 1 | 1, mid, rb);
    tg[p] = 0;
}

void push_up(int p) {
    st[p] = combine(st[p << 1], st[p << 1 | 1]);
}

void modify(int l, int r, int t, int p, int lb, int rb) {
    if (l <= lb && rb <= r) update(t, p, lb, rb);
    else {
        int mid = (lb + rb) >> 1;
        push_down(p, lb, rb);
        if (l < mid) modify(l, r, t, p << 1, lb, mid);
        if (r > mid) modify(l, r, t, p << 1 | 1, mid, rb);
        push_up(p);
    }
}

st_t query(int l, int r, int p, int lb, int rb) {
    if (l <= lb && rb <= r) return st[p];
    else {
        st_t res = { 0, LLONG_MIN, LLONG_MAX };
        int mid = (lb + rb) >> 1;
        push_down(p, lb, rb);
        if (l < mid) res = combine(res, query(l, r, p << 1, lb, mid));
        if (r > mid) res = combine(res, query(l, r, p << 1 | 1, mid, rb));
        return res;
    }
}

ll bf[N];

void gen(int id, int n, int q, int k, bool chk = false) {
    cout << id << ' ';
    this_thread::sleep_for(100ms);
    ofstream dout(to_string(id) + ".in");
    ofstream aout(to_string(id) + ".out");
    uniform_int_distribution<int> xd(1, n);
    uniform_int_distribution<int> kd(-k, k);
    uniform_int_distribution<int> od(1, 3);

    if (chk) memset(bf, 0, sizeof(bf));
    memset(st, 0, sizeof(st));
    memset(tg, 0, sizeof(tg));

    dout << n << ' ' << q << endl;
    for (int i = 0; i != q; ++i) {
        int o = od(mt), l = xd(mt), r = xd(mt);
        if (l > r) swap(l, r);
        dout << o << ' ' << l << ' ' << r;
        if (o == 1) {
            int k = kd(mt);
            dout << ' ' << k << endl;
            modify(l, r + 1, k, 1, 1, n + 1);
            if (chk) {
                for (int i = l; i <= r; ++i)
                    bf[i] += k;
            }
        }
        else if (o == 2) {
            dout << endl;
            ll res = query(l, r + 1, 1, 1, n + 1).s;
            if (chk) {
                ll bres = 0;
                for (int i = l; i <= r; ++i)
                    bres += bf[i];
                assert(res == bres);
            }
            aout << res << endl;
        }
        else if(o == 3) {
            dout << endl;
            st_t qres = query(l, r + 1, 1, 1, n + 1);
            ll res = qres.u - qres.v;
            if (chk) {
                ll u = *max_element(bf + l, bf + r + 1);
                ll v = *min_element(bf + l, bf + r + 1);
                assert(res == u - v);
            }
            aout << res <<endl;
        }
    }
}

int main(void) {
    for (int i = 1; i <= 5; ++i)
        gen(i, 10, 10, 10, true);
    for (int i = 6; i <= 10; ++i)
        gen(i, 1000, 1000, 1000, true);
    for (int i = 11; i <= 20; ++i)
        gen(i, 1000000, 1000000, 1000000, false);

    return 0;
}