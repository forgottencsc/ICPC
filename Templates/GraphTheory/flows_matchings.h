#include <bits/stdc++.h>
#define N 10001
using namespace std;


//  ISAP
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

//  你的板子很不错，但打完这场之后就变成我的了
template< typename flow_t, typename cost_t >
struct PrimalDual {
    const cost_t INF;

    struct edge {
        int to;
        flow_t cap;
        cost_t cost;
        int rev;
        bool isrev;
    };
    vector< vector< edge > > graph;
    vector< cost_t > potential, min_cost;
    vector< int > prevv, preve;

    PrimalDual(int V) : graph(V), INF(numeric_limits< cost_t >::max()) {}

    void add_edge(int from, int to, flow_t cap, cost_t cost) {
        graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(), false});
        graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size() - 1, true});
    }

    pair<flow_t, cost_t> min_cost_flow(int s, int t, flow_t f) {
        int V = (int) graph.size();
        cost_t ret = 0; flow_t f0 = 0;
        using Pi = pair< cost_t, int >;
        priority_queue< Pi, vector< Pi >, greater< Pi > > que;
        potential.assign(V, 0); preve.assign(V, -1); prevv.assign(V, -1);
        while(f > 0) {
            min_cost.assign(V, INF);
            que.emplace(0, s); min_cost[s] = 0;
            while(!que.empty()) {
                Pi p = que.top(); que.pop();
                if(min_cost[p.second] < p.first) continue;
                for(int i = 0; i < graph[p.second].size(); i++) {
                    edge &e = graph[p.second][i];
                    cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
                    if(e.cap > 0 && min_cost[e.to] > nextCost) {
                        min_cost[e.to] = nextCost;
                        prevv[e.to] = p.second, preve[e.to] = i;
                        que.emplace(min_cost[e.to], e.to);
                    }
                }
            }
            if(min_cost[t] == INF) return { f0, ret };
            for(int v = 0; v < V; v++) potential[v] += min_cost[v];
            flow_t addflow = f;
            for(int v = t; v != s; v = prevv[v])
                addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
            f -= addflow; f0 += addflow;
            ret += addflow * potential[t];
            for(int v = t; v != s; v = prevv[v]) {
                edge &e = graph[prevv[v]][preve[v]];
                e.cap -= addflow;
                graph[v][e.rev].cap += addflow;
            }
        }
        return { f0, ret };
    }
};

//  Hopcroft-Karp Algorithm
vector<int> g[N]; int n1, n2;
int lnk[N], dis[N], dm; bool vis[N];
void clr_hk(int n, int m) {
    n1 = n; n2 = m;
    for (int i = 1; i <= n1 + n2; ++i)
        g[i].clear();
}

bool bfs_hk() {
    queue<int> q; dm = INT_MAX;
    fill(dis + 1, dis + n1 + n2 + 1, -1);
    for (int i = 1; i <= n1; ++i)
        if (!lnk[i]) q.push(i), dis[i] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dis[u] > dm) break;
        for (int v : g[u]) {
            if (dis[v] != -1) continue;
            dis[v] = dis[u] + 1;
            if (!lnk[v]) dm = dis[v];
            else dis[lnk[v]] = dis[v] + 1, q.push(lnk[v]);
        }
    }
    return dm != INT_MAX;
}

int dfs_hk(int u) {
    for (int v : g[u]) {
        if (vis[v] || dis[v] != dis[u] + 1) continue;
        vis[v] = 1;
        if (lnk[v] && dis[v] == dm) continue;
        if (lnk[v] && !dfs_hk(lnk[v])) continue;
        lnk[v] = u; lnk[u] = v; return 1;
    }
    return 0;
}

int hk() {
    fill (lnk + 1, lnk + n1 + n2 + 1, 0);
    int res = 0;
    while (bfs_hk()) {
        fill (vis + 1, vis + n1 + n2 + 1, 0);
        for (int i = 1; i <= n1; ++i)
            if (!lnk[i] && dfs_hk(i)) res++;
    }
    return res;
}
