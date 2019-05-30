#include <bits/stdc++.h>
#define N 10001
using namespace std;

struct edge { int p, v, w; };
vector<edge> g[N];
int nc, cur[N], dis[N], gap[N];

void fclr() { nc = 0; }

int addn(int cnt = 1) {
    while(cnt--) {
        g[++nc].clear();
        cur[nc] = gap[nc] = 0;
        dis[nc] = -1;
    }
    return nc;
}

void adde(int u, int v, int w) {
    g[u].push_back({ g[v].size(), v, w });
    g[v].push_back({ g[u].size() - 1, u, 0 });
}

int dfs_isap(int s, int t, int u, int f) {
    if (u == t) return f;
    int sf = 0;
    for (int i = cur[u]; i != g[u].size(); ++i) {
        edge& e = g[u][i]; int v = e.v;
        if (e.w <= 0 || dis[u] != dis[v] + 1)
            continue;
        int df = dfs_isap(s, t, v, min(f, e.w));
        e.w -= df; g[v][e.p].w += df;
        f -= df; sf += df;
        if (!f) return sf;
    }
    if (!--gap[dis[u]]) dis[s] = nc;
    gap[++dis[u]]++; cur[u] = 0;
    return sf;
}

int isap(int s, int t) {
    int sf = 0; queue<int> q;
    gap[0] = 1; dis[t] = 0; q.push(t);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i != g[u].size(); ++i) {
            edge e = g[u][i]; int v = e.v;
            if (g[v][e.p].w <= 0 || dis[v] != -1)
                continue;
            dis[v] = dis[u] + 1;
            gap[dis[v]]++; q.push(v);
        }
    }
    while(dis[s] < nc) sf += dfs_isap(s, t, s, 1<<30);
    return sf;
}