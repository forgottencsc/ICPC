#include <bits/stdc++.h>
#define N 10001
using namespace std;

struct edge { int p, v; ll c, f; };
vector<edge> g[N];
int cur[N], dis[N], gap[N], nc;
const ll inf = 1ll<<20;

void fclr() { nc = 0; }

int addn(int cnt = 1) {
    while(cnt--) {
        g[++nc].clear(); dis[nc] = -1;
        cur[nc] = gap[nc] = 0;
    }
    return nc;
}

void adde(int u, int v, ll c) {
    g[u].push_back({ g[v].size(), v, c, 0 });
    g[v].push_back({ g[u].size() - 1, u, 0, 0 });
    //cout << u << ' ' << v << ' ' << c << endl;
}

ll dfs_isap(int s, int t, int u, ll f) {
    if (u == t) return f;
    ll sf = 0;
    for (int i = cur[u]; i != g[u].size(); ++i) {
        edge& e = g[u][i]; int v = e.v;
        if (e.c <= e.f || dis[u] != dis[v] + 1)
            continue;
        ll df = dfs_isap(s, t, v, min(f, e.c - e.f));
        e.f += df; g[v][e.p].f -= df;
        sf += df; f -= df; if (!f) return sf;
    }
    if (!--gap[dis[u]]) dis[s] = nc;
    gap[++dis[u]]++; cur[u] = 0;
    return sf;
}

ll isap(int s, int t, ll f = inf) {
    ll sf = 0; queue<int> q;
    gap[0] = 1; dis[t] = 0; q.push(t);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i != g[u].size(); ++i) {
            edge e = g[u][i]; int v = e.v;
            if (g[v][e.p].c <= g[v][e.p].f || dis[v] != -1)
                continue;
            dis[v] = dis[u] + 1;
            gap[dis[v]]++; q.push(v);
        }
    }
    while(dis[s] < nc) sf += dfs_isap(s, t, s, f);
    return sf;
}