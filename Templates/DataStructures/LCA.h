//  RMQ LCA O(nlogn)-O(1)
struct edge { int v, w; };
vector<edge> g[N];
int et[N << 1], ei[N], dep[N], ec; ll dis[N];
void dfs_lca(int u, int f, ll w) {
    et[++ec] = u; ei[u] = ec;
    dep[u] = dep[f] + 1; dis[u] = w;
    for (edge e : g[u]) if (e.v != f)
        dfs_lca(e.v, u, w + e.w), et[++ec] = u;
}

int lg2[N << 1], st[19][N << 1];
void build_lca() {
    for (int i = 2; i <= ec; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= ec; ++i) st[0][i] = et[i];
    for (int j = 1; (1 << j) <= ec; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= ec; ++i) {
            int u = st[j - 1][i], v = st[j - 1][i + (1 << j - 1)];
            st[j][i] = dep[u] < dep[v] ? u : v;
        }
    }
}

inline int lca(int u, int v) {
    int l = ei[u], r = ei[v];
    if (l > r) swap(l, r);
    ++r; int w = lg2[r - l];
    u = st[w][l]; v = st[w][r - (1 << w)];
    return dep[u] < dep[v] ? u : v;
}

inline ll qdis(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

//  Doubling LCA O(nlogn)-O(logn)
struct edge { int v, w; };
vector<edge> g[N];
ll mp[N][18], dis[N]; int dep[N];
void dfs_lca(int u, int f, ll w)  {
    dis[u] = w; mp[u][0] = f; dep[u] = dep[f] + 1;
    for (edge e : g[u]) if (e.v != f) dfs_lca(e.v, u, w + e.w);
}

void build_lca() {
    dfs_lca(1);
    for (int j = 1; (1 << j) <= n - 1; ++j)
        for (int i = 1; i <= n; ++i)
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
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