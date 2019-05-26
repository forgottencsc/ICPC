#include <bits/stdc++.h>
#define N 100001
using namespace std;

struct edge { int v, w; };
vector<edge> g[N];

int dep[N], mp[N][17], ms[N][17];

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, m; cin >> n >> m;
    for (int i = 0; i != n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    for (int i = 0; i != n; ++i)
        for (int j = 1; (1 << j) < n; ++j)
            ms[i][j] = INT_MAX;

    queue<int> q; q.push(1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        dep[u] = dep[mp[u][0]] + 1;
        for (edge e : g[u]) {
            if (e.v == mp[u][0]) continue;
            mp[e.v][0] = u;
            ms[e.v][0] = e.w;
            q.push(e.v);
        }
    }


    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 1; i <= n; ++i) {
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
            ms[i][j] = min(ms[i][j - 1], ms[mp[i][j - 1]][j - 1]);
        }
    }

    cout << boolalpha;
    while(m--) {
        int u, v, res = INT_MAX;
        cin >> u >> v;
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 16; dep[u] > dep[v]; --i) {
            if ((1 << i) & (dep[u] - dep[v])) {
                res = min(res, ms[u][i]);
                u = mp[u][i];
            }
        }
        if (u != v) {
            for (int i = 16; i >= 0; --i) {
                if (mp[u][i] != mp[v][i]) {
                    res = min({ res, ms[u][i], ms[v][i] });
                    u = mp[u][i];
                    v = mp[v][i];
                }
            }
            res = min({ res, ms[u][0], ms[v][0] });
        }
        cout << res << endl;
    }

    return 0;
}