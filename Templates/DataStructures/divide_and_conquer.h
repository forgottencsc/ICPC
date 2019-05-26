#include <bits/stdc++.h>
#define N 100001
using namespace std;

vector<int> g[N];
bool vis[N]; int sz[N], msz[N];
int dfs_sz(int u, int f, int s) {
    int res = msz[u] = 0; sz[u] = 1;
    for (int v : g[u]) {
        if (vis[v] || v == f) continue;
        int r = dfs_sz(v, u, s);
        sz[u] += sz[v];
        msz[u] = max(msz[u], sz[v]);
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[u] = max(msz[u], s - sz[u]);
    if (!res || msz[u] < msz[res]) res = u;
    return res;
}

int dc(int u, int s) {
    int r = dfs_sz(u, 0, s);
    vis[r] = 1;

    for (int v : g[r]) {
        if (vis[v]) continue;
        int w = dc(v, sz[v] < sz[r] ? sz[v] : s - sz[r]);

    }
    return r;
}