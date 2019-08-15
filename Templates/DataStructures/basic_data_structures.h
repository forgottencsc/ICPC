//  blocks
int bi[N], bl[M], br[M], bs, bc;
void block_init() {
    bs = sqrt(n); bc = 1; bl[1] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i - bl[bc] == bs) {
            br[bc++] = i - 1;
            bl[bc] = i;
        }
        bi[i] = bc;
    }
    br[bc] = n;
}

//  Union-Find Set, Rollback supported, O(logn)
namespace ufs {

int f[N], s[N];
int x[N], y[N], c;

void clr(int n) {
    fill(f + 1, f + n + 1, 0);
    fill(s + 1, s + n + 1, 1);
}

int find(int x) {
    while (f[x]) x = f[x];
    return x;
}

bool join(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return false;
    if (s[u] > s[v]) swap(u, v);
    ++c; x[c] = u; y[c] = v;
    s[v] += s[u]; f[u] = v;
    return true;
}

void rollback(int w) {
    for (; c != w; --c)
        f[x[c]] = 0, s[y[c]] -= s[x[c]];
}

}

//  Sparse Table
int lg2[N], st[18][N];
void build() {
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
}

int query(int l, int r) {
    int w = lg2[r - l];
    return max(st[w][l], st[w][r - (1 << w)]);
}

//  RMQ LCA O(nlogn)-O(1)
vector<int> g[N];
int et[N << 1], ei[N], ec;
void dfs_lca(int u, int f) {
    et[++ec] = u; ei[u] = ec;
    for (int v : g[u]) if (v != f)
        dfs_lca(v, u), et[++ec] = u;
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

//  Doubling LCA O(nlogn)-O(logn)
struct edge { int v, w; };
vector<edge> g[N];
ll mp[N][18], dis[N]; int dep[N];
void dfs_lca(int u, int f, ll w)  {
    dis[u] = w; mp[u][0] = f; dep[u] = dep[f] + 1;
    for (edge e : g[u])
        if (e.v != f) dfs_lca(e.v, u, w + e.w);
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

//  Vertex-DC
vector<int> g[N];
bool vis[N]; int sz[N], msz[N];
int dfs_sz(int u, int f, int s) {
    int res = msz[u] = 0; sz[u] = 1;
    for (int v : g[u]) {
        if (vis[v] || v == f) continue;
        int r = dfs_sz(v, u, s); sz[u] += sz[v];
        msz[u] = max(msz[u], sz[v]);
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[u] = max(msz[u], s - sz[u]);
    if (!res || msz[u] < msz[res]) res = u;
    return res;
}

int vdc(int u, int s) {
    vis[u = dfs_sz(u, 0, s)] = 1;

    for (int v : g[u]) {
        if (vis[v]) continue;
        int w = dc(v, sz[v] < sz[u] ? sz[v] : s - sz[u]);

    }
    return u;
}

//  Edge-DC
struct edge { int v, w; };
vector<edge> g0[N]; int n0;
vector<int> g[N]; int n; bool flg[N];
int eu[N], ev[N], ex[N], ew[N], ec; bool ef[N];
bool vis[N]; int dep[N], msz[N], sz[N];

int adde(int u, int v, int w, int f) {
    int i = ++ec;
    eu[i] = u; ev[i] = v; ex[i] = u ^ v;
    ew[i] = w; ef[i] = f; vis[i] = 0;
    g[u].push_back(i);
    g[v].push_back(i);
    //cout << u << ' ' << v << ' ' << w << endl;
    return i;
}

void dfs_rec(int u, int f) {
    int p = u, c = 0;
    for (edge e : g0[u]) {
        int v = e.v; if (v == f) continue;
        adde(p, v, e.w, 0); dfs_rec(v, u);
        if (c + 2 + !!f >= g0[u].size()) continue;
        int q = ++n; ++c; flg[q] = 1;
        adde(p, q, 0, 1); p = q;
    }
}

int dfs_sz(int i, int f, int s) {
    int res = 0, u = ex[i] ^ f;
    dep[u] = dep[f] + 1; sz[i] = 1; msz[i] = 0;
    for (int j : g[u]) {
        if (j == i || vis[j]) continue;
        int r = dfs_sz(j, u, s); sz[i] += sz[j];
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[i] = max(sz[i], s - sz[i]);
    if (!res || msz[i] < msz[res] && !vis[i]) res = i;
    return res;
}

void dfs_cnt(int u, int f, int d, int* c) {
    if (!flg[u]) c[d]++;
    for (int i : g[u])
        if (!vis[i] && (ex[i] ^ u) != f)
            dfs_cnt(ex[i] ^ u, u, (d + ew[i]) % 3, c);
}

typedef long long ll;
ll cal(int i) {
    int c1[3] = { 0 }, c2[3] = { 0 };
    dfs_cnt(eu[i], ev[i], 0, c1);
    dfs_cnt(ev[i], eu[i], 0, c2);
    ll res = 0;
    for (int d = 0; d != 3; ++d)
        res += 1ll * c1[d] * c2[(3 - (ew[i] + d) % 3) % 3];
    return res;
}

ll edc(int i, int f, int s) {
    i = dfs_sz(i, f, s);
    if (vis[i]) return 0; else vis[i] = 1;
    int u = eu[i], v = ev[i]; ll res = cal(i);
    res += edc(i, u, dep[u] > dep[v] ? s - sz[i] : sz[i]);
    res += edc(i, v, dep[v] > dep[u] ? s - sz[i] : sz[i]);
    return res;
}

ll edc() {
    ec = 0; dfs_rec(1, 0);
    int i = adde(0, 1, 0, 1);
    vis[i] = 1;
    return edc(i, 0, n);
}