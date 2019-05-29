#include <bits/stdc++.h>
#define N 300001
using namespace std;

int n, m;
vector<int> g[N];
int dfn[N], low[N], bel[N], dfc, bcc;
int bcs[N], *bct = bcs;
void bcc_clr() { fill(dfn + 1, dfn + n + 1, 0); }
int dfs_bcc(int u, int f) {
    *bct++ = u; dfn[u] = low[u] = ++dfc;
    for (int v : g[u]) {
        if (v == f) continue;
        if (!dfn[v]) low[u] = min(low[u], dfs_bcc(v, u));
        else low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u])
        for (++bcc; *bct != u; --bct)
            bel[bct[-1]] = bcc;
    return low[u];
}

vector<int> g1[N];
int d[N];

int bfs(int s) {
    fill(d + 1, d + n + 1, INT_MIN);
    queue<int> q; q.push(s); d[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g1[u]) {
            if (d[v] != INT_MIN) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return max_element(d + 1, d + n + 1) - d;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_bcc(1, 0);

    for (int u = 1; u <= n; ++u)
        for (int v : g[u])
            g1[bel[u]].push_back(bel[v]);

    for (int u = 1; u <= n; ++u) {
        sort(g1[u].begin(), g1[u].end());
        g1[u].erase(unique(g1[u].begin(), g1[u].end()), g1[u].end());
    }

    cout << d[bfs(bfs(1))] << endl;

    return 0;
}