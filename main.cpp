#include <bits/stdc++.h>
#define N 200001
typedef long long ll;
using namespace std;
typedef pair<int, int> pii;

int d[N], pos[N], rk[N];
vector<int> g[N];

int main(void){
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif // ONLINE_JUDGE
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    sort(a.begin(), a.end(), [&](int i, int j) { return d[i] > d[j]; });

    for (int i = 1; i <= n; ++i)
        pos[i] = 2 * a[i - 1] - 1, rk[2 * a[i - 1] - 1] = i;

    for (int i = 1; i <= n - 1; ++i) {
        g[pos[i]].push_back(pos[i + 1]);
    }

    int top = n;

    for (int i = 1; i <= n; ++i) {
        int u = pos[i], v = u + 1, x = i + d[(u + 1) / 2] - 1, w = pos[x];
        g[w].push_back(v);
        if (x >= top) {
            ++top;
            pos[top] = v;
            rk[v] = top;
        }
    }

    for (int i = 1; i <= 2 * n; ++i) {
        for (int j : g[i])
            cout << i << ' ' << j << endl;
    }

	return 0;
}
