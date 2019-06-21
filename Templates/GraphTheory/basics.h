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

ll g[N][N], val[N];
bool vis[N], del[N];

ll stoer_wagner(int n) {
    fill (del + 1, del + n + 1, 0);
    ll ans = LLONG_MAX;
    for (int cnt = n; cnt > 1; --cnt) {
        fill (vis + 1, vis + n + 1, 0);
        int s, t = 1; vis[1] = 1;

        for (int i = 2; i <= n; ++i) val[i]
        for (int i = cnt - 1; i; --i) {
            int u; ll wu = 0;
            for (int v = 1; v <= n; ++v) {
                if (vis[v] || del[v]) continue;
                ll wv = 0;
                for (pair<const int, ll> e : g[v])
                    if (vis[e.first]) wv += e.second;
                if (wu < wv) u = v, wu = wv;
            }
            s = t; t = u; vis[u] = 1;
        }
        ll res = 0;
        for (pair<const int, ll> e : g[t]) {
            if (vis[e.first]) res += e.second;
            if (e.first == s) continue;
            g[s][e.first] += e.second;
            g[e.first][s] += e.second;
            g[e.first].erase(t);
        }
        g[t].clear(); del[t] = 1;
        ans = min(ans, res);
    }
    return ans;
}
