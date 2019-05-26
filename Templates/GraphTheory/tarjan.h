#include <bits/stdc++.h>
using namespace std;

vector<int> g[N];

bool inst[N];
int dfn[N], low[N], bel[N], dfc, scc;
int dfs_scc(int u) {
    static stack<int> s;
    s.push(u); inst[u] = 1;
    dfn[u] = low[u] = ++dfc;
    for (int v : g[u]) {
        if (!dfn[v]) low[u] = min(low[u], dfs_scc(v));
        else if (inst[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v; ++scc;
        do bel[v = s.top()] = scc;
        while(s.pop(), inst[v] = 0, v != u);
    }
    return low[u];
}