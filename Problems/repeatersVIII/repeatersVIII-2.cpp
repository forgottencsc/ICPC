#include <bits/stdc++.h>
#define N 501
#define M 2001
using namespace std;

struct aca_t {
    int g[N][26], f[N], e[N], nc;

    int dp[M][N], cri[M][N], nxt[M][N];

    int gn() {
        int p = nc++;
        memset(g[p], 0, sizeof(g[p]));
        f[p] = e[p] = 0;
        return p;
    }

    void clr() { nc = 0; gn(); }

    void ins(const string& s, int w) {
        int p = 0;
        for (int i = 0; i != s.size(); ++i) {
            int o = s[i] - 'a';
            if (!g[p][o]) g[p][o] = gn();
            p = g[p][o];
        }
        e[p] += w;
    }

    void build() {
        queue<int> q;
        for (int o = 0; o != 26; ++o) if (g[0][o]) q.push(g[0][o]);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            e[u] += e[f[u]];
            for (int o = 0; o != 26; ++o) {
                int& v = g[u][o];
                if (!v) v = g[f[u]][o];
                else f[v] = g[f[u]][o], q.push(v);
            }
        }
    }

    int do_dp(int n) {
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j != nc; ++j)
                dp[i][j] = INT_MIN, cri[i][j] = 0, nxt[i][j] = -1;

        int ans = dp[0][0] = 0;
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != nc; ++j) {
                if (dp[i][j] == INT_MIN) continue;
                for (int o = 0; o != 26; ++o) {
                    int v = g[j][o], w = dp[i][j] + e[v];
                    int& d = dp[i + 1][v];
                    d = max(d, w);
                    ans = max(ans, w);
                }
            }
        }
        return ans;
    }

} aca;

bool chk(istream& cin, istream& cout) {
    int n, m; cin >> n;
    vector<int> val(n);
    vector<string> sv(n);
    aca.clr();
    for (int i = 0; i != n; ++i) {
        cin >> sv[i] >> val[i];
        aca.ins(sv[i], val[i]);
    }
    aca.build();
    cin >> m;
    int res = aca.do_dp(m), ans;
    cout >> ans;
    return ans == res;
}

void solve2(istream& cin, ostream& cout) {
    int n, m; cin >> n;
    vector<int> val(n);
    vector<string> sv(n);
    aca.clr();
    for (int i = 0; i != n; ++i) {
        cin >> sv[i] >> val[i];
        aca.ins(sv[i], val[i]);
    }
    aca.build();
    cin >> m;
    int res = aca.do_dp(m);
    cout << res << endl;
}

int main2(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    solve2(cin, cout);
    return 0;
}