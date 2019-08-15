#include <bits/stdc++.h>
#define N 200001
using namespace std;

typedef long long ll;

vector<int> g[N]; int dep[N];

int et[N << 1], ei[N], ec;
void dfs_lca(int u, int f) {
    dep[u] = dep[f] + 1; et[++ec] = u; ei[u] = ec;
    for (int v : g[u]) if (v != f)
        dfs_lca(v, u), et[++ec] = u;
}

int lg2[N << 1], st[19][N << 1];
void build_lca() {
    int n = ec;
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) st[0][i] = et[i];
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
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

inline int dis(int u, int v) {
    int w = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[w];
}


//
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

int fa[N]; bool wh[N]; int wc;
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii>> pq[N];

int vdc(int u, int s) {
    vis[u = dfs_sz(u, 0, s)] = 1;
    for (int v : g[u]) {
        if (vis[v]) continue;
        int w = vdc(v, sz[v] < sz[u] ? sz[v] : s - sz[u]);
        fa[w] = u;
    }
    return u;
}

void modify(int u) {
    wh[u] = !wh[u];
    if (!wh[u])
        wc--;
    else{
        wc++;
        for (int w = u; w; w = fa[w])
            pq[w].push({ dis(w, u), u });
    }
}

int query(int u) {
    int ans = INT_MAX;
    for (int w = u; w; w = fa[w]) {
        while (!pq[w].empty() && !wh[pq[w].top().second])
            pq[w].pop();
        if (!pq[w].empty())
            ans = min(ans, pq[w].top().first + dis(u, w));
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n; cin >> n;
    for (int i = 1; i <= n - 1; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_lca(1, 0);
    build();
    vdc(1, n);

    int q; cin >> q;
    while(q--) {
        int o, u; cin >> o >> u;
        if (o) {
            if (!wc)
                cout << -1 << '\n';
            else
                cout << query(u) << '\n';
        }
        else {
            modify(u);
        }
    }

    return 0;
}