#include <bits/stdc++.h>
using namespace std;

vector<int> g[N];

int dfn[N], low[N], bel[N], dfc, scc;
bool inst[N]; int scs[N], *sct = scs;
void scc_clr() { memset(dfn, 0, sizeof(dfn)); }
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