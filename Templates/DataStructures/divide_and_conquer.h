#include <bits/stdc++.h>
#define N 100001
using namespace std;

//  Vertex-DC
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

int vdc(int u, int s) {
    int r = dfs_sz(u, 0, s);
    vis[r] = 1;

    for (int v : g[r]) {
        if (vis[v]) continue;
        int w = dc(v, sz[v] < sz[r] ? sz[v] : s - sz[r]);

    }
    return r;
}

//  Edge-DC
struct edge { int v, w; };
vector<edge> g0[N];

vector<edge> g[N]; int n;
void dfs_rec(int u, int f) {
    int p = u, c = 0;
    for (edge e : g0[u]) {
        if (e.v == f) continue;
        dfs_rec(e.v, u); c++;
        g[p].push_back({ e.v, e.w });
        g[e.v].push_back({ p, e.w });
        if (c + 2 >= g0[u].size()) continue;
        int q = ++n; g[q].clear();
        g[p].push_back({ q, 0 });
        g[q].push_back({ p, 0 });
        p = q;
    }
}