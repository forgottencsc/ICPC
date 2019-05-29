#include <bits/stdc++.h>
#define N 2000001
using namespace std;

int n, m, d[N];
vector<int> g[N];

void dfs_euler(vector<int>& s, int u) {
    while(g[u].size()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs_euler(s, v);
    }
    s.push_back(u);
}

vector<int> eulerian_path() {
    int s = 0;
    vector<int> res; res.reserve(m + 1);
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end(), greater<int>());
        if (abs(d[i]) >= 2 || d[i] == 1 && s) return res;
        else if(d[i] == 1) s = i;
    }
    for (int i = 1; !s && i <= n; ++i) {
        if(g[i].empty()) continue;
        s = i;
    }
    dfs_euler(res, s);
    if(res.size() != m + 1) res.clear();
    else reverse(res.begin(), res.end());
    return res;
}