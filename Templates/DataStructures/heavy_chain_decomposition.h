#include <bits/stdc++.h>
#define N 100001
using namespace std;

int ds[N], dd[N], dh[N], df[N], di[N], di_[N], dt[N], dc;

void dfs_hcd1(int u, int f) {
    dd[u] = dd[f] + 1; dh[u] = 0;
    df[u] = f; ds[u] = 1;
    for (int v : g[u]) {
        if (v == f) continue;
        dfs_hcd1(v, u); ds[u] += ds[v];
        if (ds[dh[u]] < ds[v]) dh[u] = v;
    }
}

void dfs_hcd2(int u, int t) {
    di[u] = dc++; di_[di[u]] = u; dt[u] = t;
    if (ds[u] == 1) return;
    dfs_hcd2(dh[u], t);
    for (int v : g[u])
        if (v != df[u] && v != dh[u])
            dfs_hcd2(v, v);
}