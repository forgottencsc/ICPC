#include <bits/stdc++.h>
#define N 1001
#define P 1000000007
#define M(x) (((x) + P) % P)
using namespace std;

typedef long long ll;

ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }

ll p2[N*N], bi[N][N], inv2 = inv(2);

void init(int n) {
    for (int i = p2[0] = 1; i <= n * n; ++i)
        p2[i] = M(p2[i - 1] * 2);
    for (int i = 0; i <= n; ++i) {
        bi[i][0] = bi[i][i] = 1;
        for (int j = 1; j < i; ++j)
            bi[i][j] = M(bi[i - 1][j - 1] + bi[i - 1][j]);
    }
}

void get_connected_graph_cnt(ll* f, ll* g, int n){
    for (int i = 1; i <= n; ++i) {
        g[i] = f[i];
        for (int j = 1; j <= i - 1; ++j)
            g[i] = M(g[i] - M(bi[i - 1][j - 1] * M(g[j] * f[i - j])));
    }
}

//  f[n]: undirected graph with n vertices
//  g[n]: undirected connected graph with n vertices
void undirected_graph_cnt(ll* f, ll* g, int n) {
    for (int i = 1; i <= n; ++i)
        f[i] = p2[i * (i - 1) / 2];
    get_connected_graph_cnt(f, g, n);
}

//  f[n]: undirected eulerian graph with n vertices
//  g[n]: undirected connected graph with n vertices
void eulerian_graph_cnt(ll* f, ll* g, int n) {
    for (int i = 1; i <= n; ++i)
        f[i] = p2[(i - 1) * (i - 2) / 2];
    get_connected_graph_cnt(f, g, n);
}

//  f[n]: undirected bipartite with n vertices
//  g[n]: undirected connected bipartite with n vertices
void bipartite_cnt(ll* f, ll* g, int n) {
    static ll h[N];
    for (int i = 1; i <= n; ++i)
        for (int k = h[i] = 0; k <= i; ++k)
            h[i] = M(h[i] + bi[i][k] * p2[k * (i - k)]);
    for (int i = 1; i <= n; ++i) {
        g[i] = M(inv2 * h[i]);
        for (int j = 1; j <= i - 1; ++j)
            g[i] = M(g[i] - M(bi[i - 1][j - 1] * M(g[j] * h[i - j])));
    }
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            f[i] = M(f[i] + M(bi[i - 1][j - 1] * M(g[j] * f[i - j])));
}

//  f[n]: directed acyclic graph with n vertices
//  g[n]: directed connected acyclic graph with n vertices
void dag_cnt(ll* f, ll* g, int n) {
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k <= i; ++k)
            f[i]=M(f[i]+M(M(k&1?f[i-k]:-f[i-k])*M(bi[i][k]*p2[k*(i-k)])));
    get_connected_graph_cnt(f, g, n);
}


ll f[N][N];
//  f[n][m]: directed acyclic graph with n vertices, m zero in-degree.
void dag_cnt2(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            ll v = 1;
            for (int k = 1; k <= i - j; ++k) {
                v = M(v * M(p2[j] - 1));
                f[i][j] = M(f[i][j] +
                    M(M(bi[i][j]*v)*M(p2[j*(i-j-k)]*f[i-j][k])));
            }
        }
    }
}