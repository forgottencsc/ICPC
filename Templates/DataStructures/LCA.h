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

namespace LCA {

int dfn[N], dep[N], dfc;
ll dis[N]; int mp[N][20], m;

void dfs_lca(int u, int f, ll w) {
    if (f) dep[u] = dep[f] + 1;
    dfn[u] = ++dfc; mp[u][0] = f; dis[u] = w;
    for (int i = 1; (1 << i) <= dep[u]; ++i)
        mp[u][i] = mp[mp[u][i - 1]][i - 1];
    for (edge e : g[u]) if (e.v != f)
        dfs_lca(e.v, u, w + e.w);
}

void build(int n, int r) {
    for (m = 1; (1 << m) <= n - 1; m++);
    for (int i = 1; i <= n; ++i)
        fill_n(mp[i], m + 1, 0);
    mp[r][0] = 0;
    dfc = 0; dfs_lca(r, 0, 0);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = m; dep[u] - dep[v]; --i)
        if ((dep[u] - dep[v]) & (1 << i))
            u = mp[u][i];
    if (u == v) return u;
    for (int i = m; i >= 0; --i)
        if (mp[u][i] != mp[v][i])
            u = mp[u][i], v = mp[v][i];
    return mp[u][0];
}

ll qdis(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

}
namespace VT {

int st[N], sc;
int vs[N], vc;
vector<int> gt[N]; int rt;
int fa[N], vdep[N], sz[N];

int val[N];

int tc;

inline void gn(int u, int s) {
    sz[u] = s; gt[u].clear();
    val[u] = vdep[u] = fa[u] = 0;
    vs[++vc] = u;
}

inline void conn(int u, int v) {
    int cnt = dep[v] - dep[u] - 1;
    if (cnt) {
        int w = dfc + (++tc);
        gn(w, cnt);
        fa[v] = w; fa[w] = u;
    }
    else fa[v] = u;
}

void dfs_vdep(int u, int f) {
    vdep[u] = vdep[f] + 1;
    for (int v : gt[u]) if (v != f) dfs_vdep(v, u);
}

void build(int* us, int uc) {
    tc = vc = sc = 0;
    sort(us + 1, us + uc + 1, [](int u, int v) { return dfn[u] < dfn[v]; });
    uc = unique(us + 1, us + uc + 1) - us - 1;
    for (int i = 1; i <= uc; ++i) {
        int u = us[i]; gn(u, 1);
        if (sc) {
            int v = st[sc], w = LCA::lca(v, u);
            for (; sc > 1 && dep[w] <= dep[st[sc - 1]]; --sc)
                conn(st[sc - 1], st[sc]);
            if (w != st[sc]) {
                gn(w, 1);
                conn(w, st[sc]);
                st[sc] = w;
            }
        }
        st[++sc] = u;
    }
    for (; sc > 1; --sc) conn(st[sc - 1], st[sc]);
    for (int i = 1; i <= vc; ++i) {
        int u = vs[i], v = fa[u];
        if (!v) rt = u;
        else {
            gt[u].push_back(v);
            gt[v].push_back(u);
        }
    }
    vdep[rt] = 0; dfs_vdep(rt, 0);
}


void qry(int t, int u, int k, ll& x, ll& y) {
    if (t == 1) val[u] += k;
    if (t == 2) val[u] ^= k;
    if (t == 3) { if (val[u] >= k) val[u] -= k; }
    if (t == 4) x += 1ll * sz[u] * val[u];
    if (t == 5) { if (sz[u] & 1) x ^= val[u]; }
    if (t == 6) { x = max(x, 1ll * val[u]); y = min(y, 1ll * val[u]); }
    if (t == 7) { y = min(y, 1ll * abs(val[u] - k)); }
}

void process(query_t* qs, int q) {
    for (int i = 1; i <= q; ++i) {
        int u = qs[i].u, v = qs[i].v, t = qs[i].t, k = qs[i].k;
        if (vdep[u] < vdep[v]) swap(u, v);
        ll x = 0, y = 0;
        if (t == 4 || t == 5) x = 0;
        if (t == 6 || t == 7) x = 0, y = LLONG_MAX;
        while (vdep[u] != vdep[v]) {
            qry(t, u, k, x, y);
            u = fa[u];
        }
        while (u != v) {
            qry(t, u, k, x, y);
            qry(t, v, k, x, y);
            u = fa[u];
            v = fa[v];
        }
        qry(t, u, k, x, y);
        if (t == 4 || t == 5) cout << x << endl;
        if (t == 6) cout << x - y << endl;
        if (t == 7) cout << y << endl;
    }
}

}
