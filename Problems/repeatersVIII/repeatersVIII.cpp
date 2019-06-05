#include <bits/stdc++.h>
#define N 501
#define M 2001
using namespace std;

int g[N][26], f[N], w[N], nc;

int gn() {
    int p = nc++;
    memset(g[p], 0, sizeof(g[p]));
    f[p] = w[p] = 0;
    return p;
}

void clr() { nc = 0; gn(); }

void ins(const string& s, int val) {
    int p = 0;
    for (char ch : s) {
        int o = ch - 'a';
        if (!g[p][o]) g[p][o] = gn();
        p = g[p][o];
    }
    w[p] += val;
}

void build() {
    queue<int> q;
    for (int o = 0; o != 26; ++o) if (g[0][o]) q.push(g[0][o]);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        w[u] += w[f[u]];
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (!v) v = g[f[u]][o];
            else {
                f[v] = g[f[u]][o];
                q.push(v);
            }
        }
    }
}

int dp[M][N];

void solve(istream& cin, ostream& cout) {
    int n; cin >> n;
    clr();
    while(n--) {
        string s; int w;
        cin >> s >> w;
        ins(s, w);
    }
    build();
    int m, ans = 0; cin >> m;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j != nc; ++j) {
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i != m; ++i) {
        for (int j = 0; j != nc; ++j) {
            if (dp[i][j] == INT_MIN) continue;
            for (int o = 0; o != 26; ++o) {
                int& d = dp[i + 1][g[j][o]];
                d = max(d, dp[i][j] + w[g[j][o]]);
                ans = max(ans, d);
            }
        }
    }
    cout << ans << endl;
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    solve(cin, cout);

    return 0;
}