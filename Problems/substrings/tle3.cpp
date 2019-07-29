#include <bits/stdc++.h>
#define N 100001
#define M(x) (((x) + P) % P)
#define P 1000000007
using namespace std;

char s[N]; int n, k;
vector<int> g[N];

int bf(int u, int f, int y) {
    y = (10 * y + s[u] - '0') % k;
    int res = (y == 0);
    for (int v : g[u])
        if (v != f)
            res += bf(v, u, y);
    return res;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int T; cin >> T;
    while(T--) {
        cin >> n >> k >> s + 1;
        for (int i = 1; i <= n; ++i)
            g[i].clear();

        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int sum = 0;
        for (int i = 1; i <= n; ++i)
            sum += bf(i, 0, 0);
        cout << sum << endl;
    }
    return 0;
}