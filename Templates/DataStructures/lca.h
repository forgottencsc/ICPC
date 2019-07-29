
ll mp[N][18], dis[N]; int dep[N];
void lca_dfs(int u, int f, ll w)  {
    dis[u] = w; mp[u][0] = f; dep[u] = dep[f] + 1;
    for (edge e : g[u])
        if (e.v != f) lca_dfs(e.v, u, w + e.w);
}

void lca_init() {
    lca_dfs(1);
    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 1; i <= n; ++i)\
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 18; dep[u] != dep[v]; --i)
        if ((1 << i) & (dep[u] - dep[v]))
            u = mp[u][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; --i)
        if (mp[u][i] != mp[v][i])
            u = mp[u][i], v = mp[v][i];
    return mp[u][0];
}

ll dis(int u, int v) {
    int w = lca(u, v);
    return dis[u] + dis[v] - 2 * dis[w];
}