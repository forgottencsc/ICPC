#include <bits/stdc++.h>
#define N 300001
using namespace std;

typedef long long dbl;
typedef long long ll;
//const dbl pi = acos(-1), eps = 1e-8;
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
//dbl len(vec v) { return hypot(v.x, v.y); }
//dbl arg(vec v) { return atan2(v.y, v.x); }

vector<vec> convex_hull(vector<vec>& ps) {
    if (ps.size() <= 3) return ps;
    swap(ps[0], *min_element(ps.begin(), ps.end()));
    sort(ps.begin() + 1, ps.end(), [&](vec v1, vec v2) {
        v1 = v1 - ps[0]; v2 = v2 - ps[0];
        return (v1 ^ v2) == 0 ? v1 * v1 < v2 * v2 : (v1 ^ v2) > 0;
    });
    vector<vec> res = { ps[0], ps[1] };
    int n = res.size();
    for (int i = 2; i != ps.size(); ++i) {
        while (res.size() >= 2 && crx(res.end()[-2],res.back(),ps[i]) <= 0) res.pop_back();
        res.push_back(ps[i]);
    }
    return res;
}

vector<vec> minkovski_sum(const vector<vec>& v1, const vector<vec>& v2) {
    const int n1 = v1.size(), n2 = v2.size();
    if (!n1) return v2;
    if (!n2) return v1;
    vector<vec> d1(n1), d2(n2);
    for (int i = 0; i != n1 - 1; ++i) d1[i] = v1[i + 1] - v1[i];
    d1[n1 - 1] = v1[0] - v1[n1 - 1];
    for (int i = 0; i != n2 - 1; ++i) d2[i] = v2[i + 1] - v2[i];
    d2[n2 - 1] = v2[0] - v2[n2 - 1];
    int p = 0, q = 0; res.push_back(v1[0] + v2[0]);
    while (p != n1 && q != n2) {
        if ((d1[p] ^ d2[q]) > 0) res.push_back(res.back() + d1[p++]);
        else res.push_back(res.back() + d2[q++]);
    }
    for (; p != n1; ++p) res.push_back(res.back() + d1[p]);
    for (; q != n2; ++q) res.push_back(res.back() + d2[q]);
    res.pop_back();
    return res;
}

struct edge { int v, a, b; };
vector<edge> g0[N];
vector<int> g[N]; int nc; bool flg[N];
int eu[N], ev[N], ex[N], ea[N], eb[N], ec; bool ef[N];
bool vis[N]; int dep[N], msz[N], sz[N];

int adde(int u, int v, int a, int b, int f) {
    int i = ++ec;
    eu[i] = u; ev[i] = v; ex[i] = u ^ v;
    ea[i] = a; eb[i] = b; ef[i] = f; vis[i] = 0;
    g[u].push_back(i);
    g[v].push_back(i);
    //cout << u << ' ' << v << ' ' << a << ' ' << b << endl;
    return i;
}

void dfs_rec(int u, int f) {
    int p = u, c = 0;
    for (edge e : g0[u]) {
        int v = e.v; if (v == f) continue;
        adde(p, v, e.a, e.b, 0); dfs_rec(v, u);
        if (c + 2 + !!f >= g0[u].size()) continue;
        int q = ++nc; ++c; flg[q] = 1;
        adde(p, q, 0, 0, 1); p = q;
    }
}

int dfs_sz(int i, int f, int s) {
    int res = 0, u = ex[i] ^ f;
    dep[u] = dep[f] + 1; sz[i] = 1; msz[i] = 0;
    for (int j : g[u]) {
        if (j == i || vis[j]) continue;
        int r = dfs_sz(j, u, s); sz[i] += sz[j];
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[i] = max(sz[i], s - sz[i]);
    if (!res || msz[i] < msz[res] && !vis[i]) res = i;
    return res;
}

void dfs_cnt(int u, int f, ll a, ll b, vector<vec>& c) {
    if (!flg[u]) c.push_back({ a, b });
    for (int i : g[u])
        if (!vis[i] && (ex[i] ^ u) != f)
            dfs_cnt(ex[i] ^ u, u, a + ea[i], b + eb[i], c);
}


typedef long long ll;
void cal(int i, vector<vec>& res) {
    vector<vec> c1, c2;
    dfs_cnt(eu[i], ev[i], ea[i], eb[i], c1);
    dfs_cnt(ev[i], eu[i], 0, 0, c2);
    c1 = convex_hull(c1); c2 = convex_hull(c2);
    minkovski_sum(res, c1, c2);
}

void edc(int i, int f, int s, vector<vec>& res) {
    i = dfs_sz(i, f, s);
    if (vis[i]) return; else vis[i] = 1;
    int u = eu[i], v = ev[i]; cal(i, res);
    edc(i, u, dep[u] > dep[v] ? s - sz[i] : sz[i], res);
    edc(i, v, dep[v] > dep[u] ? s - sz[i] : sz[i], res);
}

vector<vec> edc(int n) {
    ec = 0; nc = n; dfs_rec(1, 0);
    int i = adde(0, 1, 0, 0, 1);
    vis[i] = 1;
    vector<vec> res;
    edc(i, 0, n, res);
    res.push_back({ 0, 0 });
    res = convex_hull(res);
    return res;
}

inline ll cal(vec v, ll t) {
    return v.x * t + v.y;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n - 1; ++i) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        g0[u].push_back({ v, a, b });
        g0[v].push_back({ u, a, b });
    }

    vector<vec> r = edc(n);
    int p = r.size() - 1;
    for (int i = 0; i != m; ++i) {
        while (p && cal(r[p], i) < cal(r[p - 1], i)) --p;
        ll ans = cal(r[p], i);
        cout << ans << endl;
    }

    return 0;
}