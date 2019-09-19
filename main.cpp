#include <bits/stdc++.h>
#define N 600001
#define M 2001
using namespace std;

struct query_t { int t, u, v, k; }; qs[M];

vector<int> g0[N];
int mp[N][20], dep[N], dfn[N], dfc;

void dfs_lca(int u, int f) {
    dep[u] = dep[f] + 1; mp[u][0] = f; dfn[u] = ++dfc;
    for (int i = 1; mp[u][i - 1]; ++i)
        mp[u][i] = mp[mp[u][i - 1]][i - 1];
    for (int v : g0[u]) if (v != f) dfs_lca(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; dep[u] - dep[v]; --i)
        if ((dep[u] - dep[v]) & (1 << i))
            u = mp[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (mp[u][i]) u = mp[u][i], v = mp[v][i];
    return mp[u][0];
}


int s[N], t, r[N], m;
int sz[N], val[N], fa[N];

void conn(int u, int v) {
    if (dep[v] - dep[u] != 1) {
        int w = ++n;
        fa[v] = w;
        fa[w] = u;
        r[++m] = w;
        sz[w] = dep[v] - dep[u] - 1;
    }
    else {
        fa[v] = u;

    }

}

void build_vt(vector<int>& us) {
    sort(us.begin(), us.end(), [](int u, int v) { return dfn[u] < dfn[v]; });
    for (int u : us) {
        if (!t) { s[++t] = u; continue; }
        int v = lca(s[t], u);
        while (
    }
}

void clear_vt() {
    do g[r[m]].clear(); while (--m);
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int T; cin >> T;
    while(T--) {
        int n, q; cin >> n >> q;
        for (int i = 1; i <= n - 1; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs_lca(1, 0);

        for (int i = 1; i <= q; ++i) {
            cin >> qs[i].t >> qs[i].u >> qs[i].v;
            if (t <= 3 || t == 7) cin >> qs[i].k;
        }



    }

    return 0;
}