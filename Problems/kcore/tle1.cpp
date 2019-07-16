#include <bits/stdc++.h>
#define N 1000001
using namespace std;

extern int n, m;
extern vector<int> g[N];
extern int d[N], ans[N], a[N], c[N], p[N];
extern bool vis[N];

typedef pair<int, int> pii;

void kcore1();

bool check(istream& cin, istream& cout) {
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        d[i] = a[i] = c[i] = p[i] = ans[i] = vis[i] = 0;
    }

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    kcore1();

    for (int i = 1; i <= n; ++i) {
        int a; cout >> a;
        if (a != ans[i])
            return false;
    }

    return true;
}
