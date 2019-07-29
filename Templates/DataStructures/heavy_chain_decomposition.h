#include <bits/stdc++.h>
#define N 100001
using namespace std;

vector<int> g[N];
int dd[N], df[N], dh[N], ds[N], dt[N], dl[N], dr[N], di[N], dc;
int dfs_hcd1(int u, int f) {
    dd[u] = dd[f] + 1; df[u] = f;
    dh[u] = 0; ds[u] = 1;
    for (int v : g[u]) {
        if (v == f) continue;
        ds[u] += dfs_hcd1(v, u);
        if (ds[v] > ds[dh[u]]) dh[u] = v;
    }
    return ds[u];
}

void dfs_hcd2(int u, int t) {
    dl[u] = ++dc; di[dc] = u; dt[u] = t;
    if (dh[u]) dfs_hcd2(dh[u], t);
    for (int v : g[u])
        if (v != df[u] && v != dh[u])
            dfs_hcd2(v, v);
    dr[u] = dc;
}

typedef long long ll;
ll st[1<<18], tg[1<<18]; int a[N];

void build(int p, int lb, int rb) {
    st[p] = tg[p] = 0;
    if (lb + 1 == rb) st[p] = a[di[lb]];
    else {
        int mid = (lb + rb) >> 1;
        build(p << 1, lb, mid);
        build(p << 1 | 1, mid, rb);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }
}

void modify(int l, int r, ll t, int p, int lb, int rb) {
    st[p] += (r - l) * t;
    if (l <= lb && rb <= r) tg[p] += t;
    else {
        int mid = (lb + rb) >> 1;
        if (l < mid) modify(l, min(r, mid), t, p << 1, lb, mid);
        if (r > mid) modify(max(mid, l), r, t, p << 1 | 1, mid, rb);
    }
}

ll query(int l, int r, ll t, int p, int lb, int rb) {
    if (l <= lb && rb <= r) return st[p] + (r - l) * t;
    else {
        int mid = (lb + rb) >> 1; ll res = 0; t += tg[p];
        if (l < mid) res += query(l, min(r, mid), t, p << 1, lb, mid);
        if (r > mid) res += query(max(mid, l), r, t, p << 1 | 1, mid, rb);
        return res;
    }
}

void modify(int u, int v, ll t) {
    for (; dt[u] != dt[v]; u = df[dt[u]]) {
        if (dd[u] < dd[v]) swap(u, v);
        modify(dl[dt[u]], dl[u] + 1, t, 1, 1, dc + 1);
    }
    if (dd[u] < dd[v]) swap(u, v);
    modify(dl[v], dl[u] + 1, t, 1, 1, dc + 1);
}

ll query(int u, int v) {
    ll res = 0;
    for (; dt[u] != dt[v]; u = df[dt[u]]) {
        if (dd[u] < dd[v]) swap(u, v);
        res += query(dl[dt[u]], dl[u] + 1, 0, 1, 1, dc + 1);
    }
    if (dd[u] < dd[v]) swap(u, v);
    res += query(dl[v], dl[u] + 1, t, 1, 1, dc + 1);
    return res;
}

void modify(int u, ll t) { modify(dl[u], dr[u] + 1, t, 1, 1, dc + 1); }

ll query(int u) { return query(dl[u], dr[u] + 1, 0, 1, 1, dc + 1); }