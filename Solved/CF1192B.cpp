#include <bits/stdc++.h>
#define N 100001
#define M 60 * N
using namespace std;

typedef long long ll;

struct m2 {
    int c1, c2; ll v1, v2;
    void clr() { c1 = c2 = 0; v1 = v2 = 0; }
    void ins(int c, ll v) {
        if (c1 == c) v1 = max(v1, v);
        if (c2 == c) {
            v2 = max(v2, v);
            if (v2 > v1) {
                swap(v1, v2);
                swap(c1, c2);
            }
        }
        if (c1 != c && c2 != c) {
            if (!c1) c1 = c, v1 = v;
            else if (v1 <= v) c2 = c1, v2 = v1, c1 = c, v1 = v;
            else if (!c2 || v2 < v) c2 = c, v2 = v;
        }
    }
    void ins(m2 m) {
        if (m.c1) ins(m.c1, m.v1);
        if (m.c2) ins(m.c2, m.v2);
    }
    ll get() { return v1 + v2; }
};

int ls[M], rs[M], nc;
m2 st[M]; ll tg[M];

void update(int p, ll w) {
    if (st[p].c1) st[p].v1 += w;
    if (st[p].c2) st[p].v2 += w;
    tg[p] += w;
}

void push_up(int p) {
    st[p].clr();
    st[p].ins(st[ls[p]]);
    st[p].ins(st[rs[p]]);
}

void push_down(int p) {
    if (!tg[p]) return;
    update(ls[p], tg[p]);
    update(rs[p], tg[p]);
    tg[p] = 0;
}

void build(const vector<pair<int, ll>>& d, int p, int lb, int rb) {
    if (lb + 1 == rb)
        st[p].ins(d[lb - 1].first, d[lb - 1].second);
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

int eu[N], ev[N]; ll ew[N];
struct edge { int v, i; ll w; };
vector<edge> g[N];
set<pair<ll, int>, greater<pair<ll, int>>> ans;
unordered_map<int, int> lb[N], rb[N];
int rt[N], dfc[N], dep[N], fa[N], sta[N];

int sz[N], msz[N]; bool vis[N];
int dfs_sz(int u, int f, int s) {
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

void dfs_dc(vector<pair<int, ll>>& dis, int r, int u, int f, int c, ll w, int i) {
    if (!sta[i] || dep[sta[i]] < dep[r]) sta[i] = r;
    dis.push_back({ c, w });
    lb[r][i] = ++dfc[r];
    for (edge e : g[u]) if (!vis[e.v] && e.v != f)
        dfs_dc(dis, r, e.v, u, c, w + e.w, e.i);
    rb[r][i] = dfc[r];
}

void dc(int u, int f, int s) {
    vis[u = dfs_sz(u, 0, s)] = 1;
    fa[u] = f; dep[u] = dep[f] + 1;
    if (s == 1) return;
    vector<pair<int, ll>> dis;
    for (edge e : g[u]) {
        if (vis[e.v]) continue;
        dfs_dc(dis, u, e.v, u, e.v, e.w, e.i);
        dc(e.v, u, sz[e.v] < sz[u] ? sz[e.v] : s - sz[u]);
    }
    build(dis, rt[u] = ++nc, 1, dfc[u] + 1);
    ans.insert({ st[rt[u]].get(), u });
}

void modify(int x, ll w) {
    ll dw = w - ew[x];
    int u = sta[x];
    do {
        ans.erase({ st[rt[u]].get(), u });
        int l = lb[u][x], r = rb[u][x];
        modify(l, r + 1, dw, rt[u], 1, dfc[u] + 1);
        ans.insert({ st[rt[u]].get(), u });
    } while (u = fa[u]);
}

int main(void) {
    int n, q; ll wm; scanf("%d%d%I64d", &n, &q, &wm);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v; ll w; scanf("%d%d%I64d", &u, &v, &w);
        g[u].push_back({ v, i, w });
        g[v].push_back({ u, i, w });
        eu[i] = u; ev[i] = v; ew[i] = w;
    }

    dc(1, 0, n);

    ll last = 0;
    while(q--) {
        int x; ll w; scanf("%d%I64d", &x, &w);
        x = (x + last) % (n - 1) + 1;
        w = (w + last) % wm;
        modify(x, w);
        ew[x] = w;
        last = ans.begin()->first;
        printf("%I64d\n", last);
    }

    return 0;
}