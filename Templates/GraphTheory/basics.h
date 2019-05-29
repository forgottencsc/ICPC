#include <bits/stdc++.h>
#define N 2000001
using namespace std;

int n, m, d[N];
vector<int> g[N];

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