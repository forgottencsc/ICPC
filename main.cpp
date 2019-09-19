#include <bits/stdc++.h>
#define N 500001
using namespace std;

int clr[N];
vector<int> g[N];

bool dfs(int u, int f) {
    clr[u] = 3 - clr[f];
    bool flg = 1;
    for (int v : g[u]) {
        if (!clr[v]) {
            if (!dfs(v, u))
                flg = 0;
        }
        else {
            if (clr[u] + clr[v] != 3)
                flg = 0;
        }
    }
    return flg;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
//    #ifndef ONLINE_JUDGE
//    ifstream cin("1.in");
//    #endif // ONLINE_JUDGE
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    clr[0] = 2;
    int cs = 0, cc = 0;
    for (int i = 1; i <= n; ++i) {
        if (!clr[i]) {
            if (dfs(i, 0)) cc++;
            cs++;
        }
    }

    cout << cs - 1 + (cc == cs) << endl;


    return 0;
}
