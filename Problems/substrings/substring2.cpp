#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef long long ll;

int n, k, w;
char str[N]; int s[N];
vector<int> g[N];
int sz[N], msz[N]; bool vis[N];
ll x[31]; vector<map<ll, int>> cnt;
ll p10[N]; vector<int> d;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }

ll exgcd(ll a, ll b, ll& u, ll& v) { ll d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
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

ll cnt0(int u, int f, int h, int z) {
    z = (z + p10[h] * s[u]) % k;
    ll sum = z == 0;
    for (int v : g[u])
        if (!vis[v] && v != f)
            sum += cnt0(v, u, h + 1, z);
    return sum;
}

void cntx(int u, int f, int h) {
    for (int j = 0; j != w; ++j) {
        x[j] = (x[j] + p10[h] * s[u]) % d[j];
        cnt[j][x[j]]++;
    }

    for (int v : g[u]) if (!vis[v] && v != f)
        cntx(v, u, h + 1);

    for (int j = 0; j != w; ++j)
        x[j] = (x[j] + (d[j] - p10[h] * s[u] % d[j])) % d[j];
}

ll cnty(int u, int f, int h, ll y) {
    ll sum = 0, a = p10[h], b = k - y, p = k;
    if (lce(a, b, p)) {
        ll j = lower_bound(d.begin(), d.end(), p) - d.begin();
        auto it = cnt[j].find(b);
        if (it != cnt[j].end())
            sum += it->second;
    }
    for (int v : g[u]) if (!vis[v] && v != f)
        sum += cnty(v, u, h + 1, (10 * y + s[v]) % k);
    return sum;
}

ll dc(int u, int ss) {
    int r = dfs_sz(u, 0, ss); vis[r] = 1;
    ll sum = 0;
    for (map<ll, int>& m : cnt) m.clear();
    for (int j = 0; j != w; ++j) x[j] = 0;
    cntx(u, 0, 0); sum = cnty(u, 0, 0, 0);
    for (int v : g[r]) {
        if (vis[v]) continue;
        for (map<ll, int>& m : cnt) m.clear();
        for (int j = 0; j != w; ++j) x[j] = s[r] % d[j];
        cntx(v, r, 1); sum -= cnty(v, r, 1, s[r]);
        sum += dc(v, sz[v] < sz[r] ? sz[v] : ss - sz[r]);
    }
    return sum1 + sum2;
}

//bool bf(int u, int f, int t, int w) {
//    w = (10 * w + s[u]) % k;
//    if (u == t) return w == 0;
//    else {
//        for (int v : g[u])
//            if (v != f && bf(v, u, t, w))
//                return true;
//        return false;
//    }
//}

void solve(istream& cin, ostream& cout, bool check = false) {
    cin >> n >> k >> str;
    if (n <= 1000) check = true;
    for (int i = 1; i <= n; ++i) s[i] = str[i - 1] - '0';
    for (int i = p10[0] = 1; i <= n; ++i) p10[i] = p10[i - 1] * 10 % k;
    for (int i = 1; i <= n; ++i) g[i].clear(), vis[i] = 0;

    d.clear();
    for (int i = 0; i != 30; ++i) d.push_back(k / gcd(p10[i], k));
    sort(d.begin(), d.end()); d.erase(unique(d.begin(), d.end()), d.end());
    w = d.size();
    cnt.resize(w);

    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans = dc(1, n);
    cout << ans << endl;
//
//    if (check) {
//        ll sum = 0;
//        for (int i = 1; i <= n; ++i) {
//            for (int j = 1; j <= n; ++j) {
//                if (bf(i, 0, j, 0))
//                    sum++;
//            }
//        }
//        if (sum != ans) {
//            printf("! %d %d\n", sum, ans);
//            exit(114514);
//        }
//    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    solve(cin, cout);

    return 0;
}
