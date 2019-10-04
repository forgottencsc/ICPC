#include <bits/stdc++.h>
#define N 2000001
using namespace std;

//  Strong Connected Components
vector<int> g[N];
int dfn[N], low[N], bel[N], dfc, scc;
bool inst[N]; int scs[N], *sct = scs;
void scc_clr(int n) { fill(dfn + 1, dfn + n + 1, 0); }
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
vector<int> g[N];
int dfn[N], low[N], bel[N], dfc, bcc;
int bcs[N], *bct = bcs;
void bcc_clr(int n) { fill(dfn + 1, dfn + n + 1, 0); }
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

//  Cut vertex; Usage: if (!dfn[i]) dfs_cvb(i, i);
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

//  Eulerian path in directed graph
int n, m;
vector<int> g[N];
int deg[N]; // deg[i] == out deg - in deg of vertex i
vector<int> eulerian_path() {
    vector<int> res; res.reserve(m + 1);
    int s = 0;
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

//  Eulerian path in undirect graph

int deg[N];
typedef pair<int, int> pii;
vector<pii> g[N];

void adde(int u, int v) {
    if (u != v) {
        g[u].push_back({ v, g[v].size() });
        g[v].push_back({ u, g[u].size() - 1 });
    }
    else {
        g[u].push_back({ u, g[u].size() });
    }
}

int eulerian_path(int* r, int w) {
    static int s[N], t; int m = 0; s[++t] = w;
    while (t) {
        int u = s[t];
        if (g[u].empty())
            r[++m] = u, --t;
        else {
            pii p = g[u].back();
            int v = p.first, i = p.second;
            if (v != u) {
                if (i + 1 != g[v].size()) {
                    pii& q = g[v].back();
                    g[q.first][q.second].second = i;
                    swap(g[v][i], q);
                }
                g[u].pop_back();
                g[v].pop_back();
                s[++t] = v;
            }
            else {
                g[u].pop_back();
                s[++t] = u;
            }
        }
    }
    return m;
}

//  minimum mean weight cycle
typedef double dbl;
struct edge { int v; dbl w; };
vector<edge> g[N];

dbl dp[N][N];
dbl minmwc(int n) {
    for (int i = 1; i <= n; ++i)
        g[n + 1].push_back({ i, 0 });
    n++;
    for (int i = 1; i <= n; ++i)
        dp[i][0] = DBL_MAX;
    dp[n][0] = 0;
    for (int k = 0; k < n; ++k) {
        for (int u = 0; u <= n; ++u)
            dp[u][k + 1] = DBL_MAX;
        for (int u = 0; u <= n; ++u)
            if (dp[u][k] != DBL_MAX)
                for (edge e : g[u])
                    dp[e.v][k + 1] = min(dp[e.v][k + 1], dp[u][k] + e.w);
    }
    dbl ans = DBL_MAX;
    for (int u = 1; u <= n; ++u) {
        if (dp[u][n] == DBL_MAX) continue;
        dbl res = -DBL_MAX;
        for (int k = 0; k < n; ++k)
            if (dp[u][k] != DBL_MAX)
                res = max(res, (dp[u][n] - dp[u][k]) / (n - k));
        ans = min(ans, res);
    }
    return ans;
}

//  Steiner tree
typedef long long ll;
typedef pair<ll, int> pli;
struct edge { int v; ll w; };
vector<edge> g[N];

ll dp[1 << W][N]; int tag[N];
vector<ll> steiner_tree(int n, const vector<int>& e) {
    int w = e.size();
    fill(tag + 1, tag + n + 1, 0);
    for (int s = 1; s != 1 << w; ++s)
        fill(dp[s] + 1, dp[s] + n + 1, LLONG_MAX);
    for (int i = 0; i != w; ++i)
        tag[e[i]] = 1 << i, dp[1 << i][e[i]] = 0;
    for (int s = 1; s != 1 << w; ++s) {
        priority_queue<pli> q;
        for (int u = 1; u <= n; ++u) {
            for (int t = s & (s - 1); t; t = s & (t - 1)) {
                ll v1 = dp[t][u], v2 = dp[s ^ t][u];
                if (v1 != LLONG_MAX && v2 != LLONG_MAX)
                    dp[s][u] = min(dp[s][u], v1 + v2);
            }
            if (dp[s][u] != LLONG_MAX)
                q.push({ dp[s][u], u });
        }
        while (!q.empty()) {
            pli p = q.top(); q.pop();
            int u = p.second; ll du = p.first;
            if (du > dp[s][u]) continue;
            for (edge e : g[u]) {
                int v = e.v; ll dv = e.w + du;
                if (dp[s][v] > dv)
                    q.push({ dp[s][v] = dv, v });
            }
        }
    }
    vector<ll> res(1 << w);
    for (int s = 0; s != 1 << w; ++s)
        res[s] = *min_element(dp[s] + 1, dp[s] + n + 1);
    return res;
}

vector<int> g[N];

int deg[N]; bool del[N];
void encode_tree(int* p, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    fill(del + 1, del + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        deg[i] = g[i].size();
        if (deg[i] == 1)
            pq.push(i);
    }
    for (int i = 1; i <= n - 2; ++i) {
        int u = pq.top(), v; pq.pop(); del[u] = 1;
        for (int w : g[u]) if (!del[w]) v = w;
        p[i] = v; if (--deg[v] == 1) pq.push(v);
    }
}

int cnt[N];
void decode_tree(int* p, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n - 2; ++i) cnt[p[i]]++;
    for (int i = 1; i <= n; ++i) if (!cnt[i]) pq.push(i);
    for (int i = 1; i <= n - 2; ++i) {
        int u = p[i], v = pq.top(); pq.pop();
        g[u].push_back(v);
        g[v].push_back(u);
        if (!--cnt[u]) pq.push(u);
    }
    int u = pq.top(); pq.pop();
    int v = pq.top(); pq.pop();
    g[u].push_back(v);
    g[v].push_back(u);
}
