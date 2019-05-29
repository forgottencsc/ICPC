#include <bits/stdc++.h>
#define N 2000001
using namespace std;

//  Strong Connected Components
int n, m;
vector<int> g[N];
int dfn[N], low[N], bel[N], dfc, scc;
bool inst[N]; int scs[N], *sct = scs;
void scc_clr() { fill(dfn + 1, dfn + n + 1, 0); }
int dfs_scc(int u) {
    *sct++ = u; inst[u] = 1;
    dfn[u] = low[u] = ++dfc;
    for (int v : g[u]) {
        if (!dfn[v]) low[u] = min(low[u], dfs_scc(v));
        else if (inst[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
        for (++scc; *sct != u; --sct)
            bel[sct[-1]] = scc, inst[sct[-1]] = 0;
    return low[u];
}

//  Biconnected Components
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

int n, m;
vector<int> g[N];
int deg[N]; // deg[i] == out deg - in deg of vertex i
vector<int> eulerian_path() {
    int s = 0;
    vector<int> res; res.reserve(m + 1);
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end(), greater<int>());
        if (abs(deg[i]) >= 2 || deg[i] == 1 && s) return res;
        else if(deg[i] == 1) s = i;
    }
    for (int i = 1; !s && i <= n; ++i) {
        if(g[i].empty()) continue;
        s = i;
    }
    vector<int> stk; stk.reserve(n + 1);
    stk.push_back(s);
    while(!stk.empty()) {
        int u = stk.back();
        if (g[u].empty()) res.push_back(u), stk.pop_back();
        else stk.push_back(g[u].back()), g[u].pop_back();
    }
    if(res.size() != m + 1) res.clear();
    else reverse(res.begin(), res.end());
    return res;
}