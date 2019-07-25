#include <bits/stdc++.h>
#define N 2000001
using namespace std;

struct edge { int v, w, d[2]; };
vector<edge> g[N];

int dp[N][2], sum[N];

void dfs1(int u, int f) {
    for (edge& e : g[u]) {
        int v = e.v; if (v == f) continue;
        dfs1(v, u); sum[u] += dp[v][0];
    }

    for (edge e : g[u]) {
        int v = e.v; if (v == f) continue;
        e.d[0] = dp[v][0];
        e.d[1] = dp[v][1];
        dp[u][0] = max(dp[u][0], dp[v][0]);
        dp[u][1] = max(dp[u][1], sum[u] + dp[v][1] - dp[v][0]);
    }
}

void dfs2(int u, int f) {

}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    solve(cin, cout);

    return 0;
}