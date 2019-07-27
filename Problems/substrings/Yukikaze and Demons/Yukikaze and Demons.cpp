#include <bits/stdc++.h>
#define N 50001
using namespace std;

typedef long long ll;

int n, k, w; vector<int> d;
char str[N]; int s[N];
ll p10[N];

vector<int> g[N];
int sz[N], msz[N]; bool vis[N];
int x[31]; vector<map<int, int>> cnt;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }
int exgcd(int a, int b, int& u, int& v) { int d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

bool lce(int& a, int& b, int& p) {
	int x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) a = 1, b = mod(x * b / d, p /= d);
	return a == 1;
}

int dfs_sz(int u, int f, int s) {
    int res = msz[u] = 0; sz[u] = 1;
    for (int v : g[u]) {
        if (vis[v] || v == f) continue;
        int r = dfs_sz(v, u, s);
        sz[u] += sz[v];
        msz[u] = max(msz[u], sz[v]);
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[u] = max(msz[u], s - sz[u]);
    if (!res || msz[u] < msz[res]) res = u;
    return res;
}

void cntx(int u, int f, int h) {
    for (int j = 0; j != w; ++j)
        cnt[j][x[j] = (x[j] + p10[h] * s[u]) % d[j]]++;
    for (int v : g[u]) if (!vis[v] && v != f)
        cntx(v, u, h + 1);
    for (int j = 0; j != w; ++j)
        x[j] = (x[j] + (d[j] - p10[h] * s[u] % d[j])) % d[j];
}

int cnty(int u, int f, int h, ll y) {
    int sum = 0, a = p10[h], b = k - y, p = k;
    if (lce(a, b, p)) {
        ll j = lower_bound(d.begin(), d.end(), p) - d.begin();
        auto it = cnt[j].find(b);
        if (it != cnt[j].end()) sum += it->second;
    }
    for (int v : g[u]) if (!vis[v] && v != f)
        sum += cnty(v, u, h + 1, (10 * y + s[v]) % k);
    return sum;
}

int dc(int u, int ss) {
    int r = dfs_sz(u, 0, ss); vis[r] = 1;
    int sum = 0;
    for (map<int, int>& m : cnt) m.clear();
    for (int j = 0; j != w; ++j) x[j] = 0;
    cntx(r, 0, 0); sum = cnty(r, 0, 0, 0);
    for (int v : g[r]) {
        if (vis[v]) continue;
        for (map<int, int>& m : cnt) m.clear();
        for (int j = 0; j != w; ++j) x[j] = s[r] % d[j];
        cntx(v, r, 1); sum -= cnty(v, r, 1, s[v]);
        sum += dc(v, sz[v] < sz[r] ? sz[v] : ss - sz[r]);
    }
    return sum;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--) {
        cin >> n >> k >> str;
        for (int i = p10[0] = 1; i <= n; ++i) p10[i] = p10[i - 1] * 10 % k;
        for (int i = 1; i <= n; ++i) g[i].clear(), vis[i] = 0;
        for (int i = 1; i <= n; ++i) s[i] = str[i - 1] - '0';
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        d.clear();
        for (int i = 0; i != 30; ++i) d.push_back(k / gcd(p10[i], k));
        sort(d.begin(), d.end()); d.erase(unique(d.begin(), d.end()), d.end());
        cnt.resize(w = d.size());
        cout << dc(1, n) << endl;
    }
    return 0;
}