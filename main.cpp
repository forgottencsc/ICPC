#include <bits/stdc++.h>
using namespace std;

typedef int ll;

template< typename flow_t, typename cost_t >
struct PrimalDual {
    typedef pair<cost_t, int> pii;
    const cost_t INF;

    struct edge { int v, p; flow_t w; cost_t c;  };
    vector< vector< edge > > g;
    vector< cost_t > pot, d;
    vector< int > pv, pe;

    PrimalDual(int V) : g(V), INF(numeric_limits< cost_t >::max()) {}

    void add_edge(int u, int v, flow_t w, cost_t c) {
        g[u].emplace_back((edge) {v, g[v].size(), w, c});
        g[v].emplace_back((edge) {u, g[u].size() - 1, 0, -c});
    }

    pair<flow_t, cost_t> min_cost_flow(int s, int t, flow_t f) {
        int V = g.size();
        flow_t flow = 0;
        cost_t cost = 0;
        priority_queue<pii, vector<pii>, greater<pii>> q;
        pot.assign(V, 0); pe.assign(V, -1); pv.assign(V, -1);
        while(f > 0) {
            d.assign(V, INF);
            q.push({ d[s] = 0, s });
            while(!q.empty()) {
                pii p = q.top(); q.pop();
                int u = p.second; cost_t du = p.first;
                if(d[u] < du) continue;
                for(int i = 0; i != g[u].size(); ++i) {
                    edge& e = g[u][i];
                    cost_t dv = du + e.c + pot[u] - pot[e.v];
                    if(e.w > 0 && d[e.v] > dv) {
                        d[e.v] = dv; pv[e.v] = u, pe[e.v] = i;
                        q.emplace(d[e.v], e.v);
                    }
                }
            }
            if(d[t] == INF) return { flow, cost };
            for(int v = 0; v < V; v++) pot[v] += d[v];
            flow_t df = f;
            for(int v = t; v != s; v = pv[v])
                df = min(df, g[pv[v]][pe[v]].w);
            f -= df; flow += df; cost += df * pot[t];
            for(int v = t; v != s; v = pv[v]) {
                edge &e = g[pv[v]][pe[v]];
                e.w -= df; g[v][e.p].w += df;
            }
        }
        return { flow, cost };
    }
};

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int n, m; cin >> n >> m;
    PrimalDual<ll, ll> mcmf(n + 1);
    while(m--) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        mcmf.add_edge(u, v, w, c);
    }
    pair<ll, ll> res = mcmf.min_cost_flow(1, n, mcmf.INF);
    cout << res.first << ' ' << res.second << endl;


    return 0;
}