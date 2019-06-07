#include <bits/stdc++.h>
#define N 1000002
using namespace std;
typedef long long ll;

char s[N]; int n;
int g[N][10], f[N], l[N], nc;
ll w[N], p10[N], t;

int gn(int len, int fail) {
    int p = nc++; l[p] = len; f[p] = fail;
    memset(g[p], 0, sizeof(g[p]));
    return p;
}

void clr() { nc = n = 0; s[0] = -1; gn(0, 1); gn(-1, -1); }

int gf(int p) {
    while (s[n] != s[n - l[p] - 1])
        p = f[p];
    return p;
}

int extend(int p, int o) {
    s[++n] = o; p = gf(p);
    int& q = g[p][o];
    if (!q) {
        q = gn(l[p] + 2, g[gf(f[p])][o]);
        if (l[p] == -1) w[q] = o;
        else w[q] = (w[p] * 10 + (p10[l[p] + 1] + 1) * o) % t;
    }
    return q;
}

void solve(istream& cin, ostream& cout) {
    string s; cin >> s >> t;
    for (int i = p10[0] = 1; i != N; ++i)
        p10[i] = (p10[i - 1] * 10) % t;
    clr(); int p = 0;
    for (char ch : s)
        p = extend(p, ch - '0');
    ll ans = 0;
    for (int i = 2; i != nc; ++i)
        ans = (ans + w[i]) % t;
    cout << ans << endl;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    solve(cin, cout);
    return 0;
}
