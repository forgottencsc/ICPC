#include <bits/stdc++.h>
#define N 300001
using namespace std;

typedef long long ll;
//  Usage: if (!dfn[i]) dfs_cvb(i, i);
vector<int> g[N];
int dfn[N], low[N], dfc; bool cv[N];
void cvb_clr(int n) { fill(dfn + 1, dfn + n + 1, 0); }
int dfs_cvb(int u, int r) {
    dfn[u] = low[u] = ++dfc;
    int cnt = 0;
    for (int v : g[u]) {
        if (!dfn[v]) {
            low[u] = min(low[u], dfs_cvb(v, r));
            if (low[v] == dfn[u] && u != r) cv[u] = 1;
            if (u == r) ++cnt;
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if (u == r && cnt >= 2) cv[u] = 1;
    return low[u];
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, m; cin >> n >> m;
    vector<pair<int, int>> es;
    cvb_clr(n);
    for (int i = 0; i != m; ++i) {
        int u, v; cin >> u >> v;
        //es.emplace_back(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) dfs_cvb(i, i);

    vector<int> cvs;
    for (int i = 1; i <= n; ++i)
        if (cv[i]) cvs.push_back(i);

    cout << cvs.size() << endl;
    for (int i = 0; i != cvs.size(); ++i)
        cout << cvs[i] << " \n"[i == cvs.size() - 1];
    cout.flush();
    return 0;
}