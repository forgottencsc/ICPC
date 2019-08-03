#include <bits/stdc++.h>
#define N 100001
using namespace std;

struct edge { int v, w; };
vector<edge> g0[N];

vector<edge> g[N]; int n;

void dfs_rec(int u, int f) {
    int p = u, c = 0;
    for (edge e : g0[u]) {
        if (e.v == f) continue;
        dfs_rec(e.v, u); c++;
        g[p].push_back({ e.v, e.w });
        g[e.v].push_back({ p, e.w });
        if (c + 2 >= g0[u].size()) continue;
        int q = ++n; g[q].clear();
        g[p].push_back({ q, 0 });
        g[q].push_back({ p, 0 });
        p = q;
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    cin >> n;
    for (int i = 0; i != n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g0[u].push_back({ v, 0 });
        g0[v].push_back({ u, 0 });
    }

    dfs_rec(1, 0);
    for (int i = 1; i <= n; ++i) {
        for (edge e : g[i])
            cout << e.v << ' ';
        cout << endl;
    }

    return 0;
}
