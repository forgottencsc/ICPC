#include <bits/stdc++.h>
#define N 100001
using namespace std;

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
        int v = e.v;
        if (v == f) continue;
        adde(p, v, e.w, 0);
        dfs_rec(v, u);
        if (c + 2 + !!f >= g0[u].size()) continue;
        int q = ++n; ++c; flg[q] = 1;
        adde(p, q, 0, 1);
        p = q;
    }
}

int dfs_sz(int i, int f, int s) {
    int res = 0, u = ex[i] ^ f;
    dep[u] = dep[f] + 1;
    sz[i] = 1; msz[i] = 0;
    for (int j : g[u]) {
        if (j == i || vis[j]) continue;
        int r = dfs_sz(j, u, s);
        sz[i] += sz[j];
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
    int c1[3] = { 0 };
    int c2[3] = { 0 };
    dfs_cnt(eu[i], ev[i], 0, c1);
    dfs_cnt(ev[i], eu[i], 0, c2);
    ll res = 0;
    for (int d = 0; d != 3; ++d)
        res += 1ll * c1[d] * c2[(3 - (ew[i] + d) % 3) % 3];
    return res;
}

ll edc(int i, int f, int s) {
    i = dfs_sz(i, f, s);
    if (vis[i]) return 0;
    else vis[i] = 1;
    int u = eu[i], v = ev[i];
    ll res = cal(i);
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

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    cin >> n0; n = n0;
    for (int i = 1; i <= n - 1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g0[u].push_back({ v, w });
        g0[v].push_back({ u, w });
    }

    ll res = edc();

    ll u = res * 2 + n0, v = n0 * n0, d = gcd(u, v);
    u /= d; v /= d;
    cout << u << '/' << v << endl;
    return 0;
}