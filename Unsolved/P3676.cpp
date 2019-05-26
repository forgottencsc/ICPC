#include <bits/stdc++.h>
#define N 200001
#define endl '\n'
using namespace std;
typedef long long ll;

int val[N];
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

ll s1[N], s2[N]; int fa[N];
int dc(int u, int s) {
    int r = dfs_sz(u, 0, s); vis[r] = 1;
    s1[r] = val[r]; s2[r] = 0;
    for (int v : g[r]) {
        if (vis[v]) continue;
        int w = dc(v, sz[v] < sz[r] ? sz[v] : s - sz[r]);
        fa[w] = r;
        s1[r] += s1[w];
        s2[r] += s2[w];
    }
    s2[r] += s1[w] * s1[w];
    return r;
}

void modify(int s, int w) {
    vector<int> vl; vl.push_back(s);
    for (int v = fa[s]; v; v = fa[v])
        vl.push_back(v);
    reverse(vl.begin(), vl.end());
    for (int i = 0; i != vl.size() - 1; ++i) {
        int v = vl[i], u = vl[i + 1];
        s2[v] -= s1[v] * s1[v] + s2[u];
        s1[v] -= s1[u];
    }
    s2[s] -= s1[s] * s1[s];
    s1[s] -= val[s];
    val[s] = w;
    s1[s] += val[s];
    s2[s] += s1[s] * s1[s];
    reverse(vl.begin(), vl.end());
    for (int i = 0; i != vl.size() - 1; ++i) {
        int v = vl[i], u = vl[i + 1];
        s1[u] += s1[v];
        s2[u] += s1[u] * s1[u] + s2[v];
    }
}

ll query(int s, int r) {
    ll res = s2[s];

}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, q; cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    int r = dc(1, n);
    while(q--) {
        int o; cin >> o;
        if (o == 1) {
            int x, y;
            cin >> x >> y;
            modify(x, y);
        }
        else {
            int x; cin >> x;
            cout << query(x, r) << endl;
        }
    }

    return 0;
}