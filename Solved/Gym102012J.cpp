#include <bits/stdc++.h>
#define N 100001
#define W 100
#define M(x) (((x) + P) % P)
#define P 1000000007
#define lson p << 1, lb, mid
#define rson p << 1 | 1, mid, rb
#define root 1, 1, n + 1
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
inline void apply(pll& p1, pll p2) {
    if (p1.first < p2.first)
        p1 = p2;
    else if(p1.first == p2.first)
        p1.second = M(p1.second + p2.second);
}

pll st[1<<18];
pll res[N];

inline void push_down(int p) {
    if (st[p].first == -1) return;
    apply(st[p << 1], st[p]);
    apply(st[p << 1 | 1], st[p]);
    st[p] = { -1, 0 };
}

void build(int p, int lb, int rb) {
    st[p] = { -1, 0 };
    if (lb + 1 == rb) res[lb] = { -1, 0 };
    else {
        int mid = (lb + rb) >> 1;
        build(lson);
        build(rson);
    }
}

void modify(int l, int r, pll v, int p, int lb, int rb) {
    if (l <= lb && rb <= r) apply(st[p], v);
    else {
        int mid = (lb + rb) >> 1;
        push_down(p);
        if (l < mid) modify(l, r, v, lson);
        if (r > mid) modify(l, r, v, rson);
    }
}

void query(int p, int lb, int rb) {
    if (lb + 1 == rb) res[lb] = st[p];
    else {
        int mid = (lb + rb) >> 1;
        push_down(p);
        query(lson);
        query(rson);
    }
}

vector<int> g1[N], g2[N];
int w[N], c[N];

pll dp1[N][W], dp2[N][W];
int deg[N], pos[N], rk[N];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            g1[i].resize(0);
            g2[i].resize(0);
            deg[i] = 0;
        }

        for (int i = 1; i <= n; ++i)
            cin >> w[i] >> c[i];
        for (int i = 1; i <= m; ++i) {
            int u, v; cin >> u >> v;
            g1[u].push_back(v);
            g2[v].push_back(u);
            deg[v]++;
        }
        int s, t; cin >> s >> t;
        for (int i = 1; i <= n; ++i) {
            w[i] %= s;
            for (int j = 0; j != s; ++j)
                dp1[i][j] = dp2[i][j] = { -1, 0 };
        }

        dp1[n][w[n]] = { c[n], 1 };
        dp2[1][w[1]] = { c[1], 1 };

        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (!deg[i]) pos[++cnt] = i;
        for (int i = 1; i <= n; ++i)
            for (int v : g1[pos[i]])
                if (!--deg[v]) pos[++cnt] = v;
        for (int i = 1; i <= n; ++i)
            rk[pos[i]] = i;

        for (int i = 1; i <= n; ++i) {
            int u = pos[i];
            for (int v : g2[u])
                for (int k = 0; k != s; ++k)
                    if (dp2[v][k].first != -1)
                        apply(dp2[u][(k+w[u])%s], { dp2[v][k].first + c[u], dp2[v][k].second });
        }

        for (int i = n; i >= 1; --i) {
            int u = pos[i];
            for (int v : g1[u])
                for (int k = 0; k != s; ++k)
                    if (dp1[v][k].first != -1)
                        apply(dp1[u][(k+w[u])%s], { dp1[v][k].first + c[u], dp1[v][k].second });
        }

        build(root);

        for (int u = 1; u <= n; ++u) {
            for (int v : g1[u]) {
                int x = rk[u] + 1, y = rk[v] - 1;
                if (x > y) continue;
                pll b = { -1, 0 };
                for (int k = 0; k != s; ++k) {
                    pll v1 = dp2[u][k], v2 = dp1[v][(t - k + s) % s];
                    if (v1.first == -1 || v2.first == -1) continue;
                    apply(b, { v1.first + v2.first, M(v1.second * v2.second) });
                }
                if (b.first != -1)
                    modify(x, y + 1, b, root);
            }
        }

        if (rk[1] != 1)
            modify(1, rk[1], dp1[1][t], root);

        if (rk[n] != n)
            modify(rk[n] + 1, n + 1, dp2[n][t], root);

        query(root);

        for (int i = 1; i <= n; ++i) {
            int e = rk[i];
            if (res[e].first != -1)
                cout << res[e].first << ' ' << res[e].second << '\n';
            else
                cout << -1 << '\n';
        }

    }

    return 0;
}