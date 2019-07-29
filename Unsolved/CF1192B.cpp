#include <bits/stdc++.h>
#define N 100001
#define M 40 * N
using namespace std;

typedef long long ll;

struct max2 {
    ll v1, v2;
    max2() : v1(-1), v2(-1) {}
    void ins(ll v) { if(v >= v1) v2 = v1, v1 = v; else if(v > v2) v2 = v; }
    ll get() const { return v2 == -1 ? 0 : v1 + v2; }
};
max2 combine(max2 m1, max2 m2) { m1.ins(m2.v1); m1.ins(m2.v2); return m1; }
int ls[M], rs[M], nc;
max2 st[M]; ll tg[N];


void update(int p, ll w) {
    if (st[p].v1 != -1) st[p].v1 += w;
    if (st[p].v2 != -1) st[p].v2 += w;
    tg[p] += w;
}

void push_down(int p) {
    update(ls[p], tg[p]);
    update(rs[p], tg[p]);
    tg[p] = 0;
}

void push_up(int p) {
    st[p] = combine(st[ls[p]], st[rs[p]]);
}

void build(const vector<ll>& d, int p, int lb, int rb) {
    if (lb + 1 == rb) st[p].ins(d[lb - 1]);
    else {
        int mid = (lb + rb) >> 1;
        build(d, ls[p] = ++nc, lb, mid);
        build(d, rs[p] = ++nc, mid, rb);
        push_up(p);
    }
}

void modify(int l, int r, ll w, int p, int lb, int rb) {
    if (l <= lb && rb <= r) update(p, w);
    else {
        int mid = (lb + rb) >> 1;
        push_down(p);
        if (l < mid) modify(l, r, w, ls[p], lb, mid);
        if (r > mid) modify(l, r, w, rs[p], mid, rb);
        push_up(p);
    }
}

struct edge { int v, w, i; };
vector<edge> g[N];

int fa[N], cd[N]; ll ans[N];
int eu[N], ev[N]; ll ew[N];
map<int, int> id[N], bl[N], br[N];
map<int, int> lwr[N];
vector<ll> dis[N];
int dfc[N], rt[N];

int sz[N], msz[N]; bool vis[N];
void dfs_dc(vector<ll>& dis, int r, int u, int f, int& c, ll w) {
    id[r][u] = ++c;
    bl[r][u] = c;
    dis.push_back(w);
    for (edge e : g[u])
        if (!vis[e.v] && e.v != f)
            dfs_dc(dis, r, e.v, u, c, w + e.w), lwr[r][e.i] = u;
    br[r][u] = c;
}

int dfs_sz(int u, int f, int s){
    int res = 0; sz[u] = 1; msz[u] = 0;
    for (edge e : g[u]) {
        if (e.v == f || vis[e.v]) continue;
        int r = dfs_sz(e.v, u, s);
        sz[u] += sz[e.v];
        msz[u] = max(msz[u], sz[e.v]);
        if (!res || msz[r] < msz[res]) res = r;
    }
    msz[u] = max(msz[u], s - sz[u]);
    if (!res || msz[u] < msz[res]) res = u;
    return res;
}

set<pair<ll, int>, greater<pair<ll, int>>> gans;

int dc(int u, int s, int c) {
    u = dfs_sz(u, 0, s); vis[u] = 1; cd[u] = c;
    vector<ll> dis;
    dfs_dc(dis, u, u, 0, dfc[u], 0);
    build(dis, rt[u] = ++nc, 1, dfc[u] + 1);
    ans[u] = st[rt[u]].get();
    gans.insert({ ans[u], u });
    for (edge e : g[u]) {
        if (vis[e.v]) continue;
        fa[dc(e.v, s, c + 1)] = u;
    }
}

void modify(int i, ll w) {
    int r = dc[eu[i]] < dc[ev[i]] ? eu[i] : ev[i];
    do {
        int p = lwr[r][i];
        gans.erase({ ans[r], r });
        modify(bl[r][p], br[r][p] + 1, w - ew[i], rt[r], 1, dfc[r] + 1);
        ans[r] = st[rt[r]].get();
        gans.insert({ ans[r], r });
    } while(r = fa[r]);
    ew[i] = w;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, q; ll wm; cin >> n >> q >> wm;
    for (int i = 1; i <= n - 1; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        eu[i] = u; ev[i] = v; ew[i] = w;
        g[u].push_back({ v, w, i });
        g[v].push_back({ u, w, i });
    }

    dc(1, n, 1);

    ll lans = 0;
    while (q--) {
        int d, e;
        cin >> d >> e;
        d = (d + lans) % (n - 1);
        e = (e + lans) % wm;
        modify(d + 1, e);
        auto it = gans.begin();
        lans = it->first + next(it)->first;
        cout << lans << endl;
    }
    return 0;
}