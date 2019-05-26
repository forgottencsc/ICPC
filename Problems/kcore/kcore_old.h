#include <bits/stdc++.h>
#define N 1000001

using namespace std;

vector<int> g[N];

int c[N], a[N], d[N], s[N], p[N], n;

int cores() {
    for (int i = 1; i <= n; ++i) {
        d[i] = g[i].size();
        s[d[i]]++;
    }
    for (int i = 1; i <= n; ++i)
        s[i] += s[i - 1];
    for (int i = 1; i <= n; ++i)
        a[p[i] = s[d[i]]--] = i;
    for (int i = 1; i <= n; ++i)
        s[i]++;
    int w = 0;
    for (int i = 1; i <= n; ++i) {
        int u = a[i];
        while(w < d[u]) ++w;
        c[u] = w;
        for (int v : g[u]) {
            if (c[v]) continue;
            s[d[u]]++; d[u]--;
            int x = v, y = a[s[d[v]]];
            swap(p[x], p[y]);
            swap(a[p[x]], a[p[y]]);
            s[d[v]]++; d[v]--;
        }
    }
    return w;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ans = cores();
    cout << ans << endl;
    vector<int> v(ans + 1, 0);
    for (int i = 1; i <= n; ++i)
        v[c[i]]++;
    for (int i = 0; i <= ans; ++i)
        cout << v[i] << ' ';
    cout << endl;

    return 0;
}

