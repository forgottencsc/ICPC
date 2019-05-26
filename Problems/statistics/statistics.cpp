#include <bits/stdc++.h>
#define N (1<<20)
#define endl '\n'
using namespace std;

typedef long long ll;

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

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, q; cin >> n >> q;
    while(q--) {
        int o, l, r; cin >> o >> l >> r;
        if (o == 1) {
            int k; cin >> k;
            modify(l, r + 1, k, 1, 1, n + 1);
        }
        else if(o == 2) {
            st_t qres = query(l, r + 1, 1, 1, n + 1);
            cout << qres.s << endl;
        }
        else if(o == 3) {
            st_t qres = query(l, r + 1, 1, 1, n + 1);
            cout << qres.u - qres.v << endl;
        }
    }
}