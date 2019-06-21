#include <bits/stdc++.h>
#define N 1000005
#define M 21 * N
using namespace std;

int pos[N], nid[N];

int g[N][26], f[N], l[N], nc;

int gn(int l_, int q = 0) {
    int p = nc++; l[p] = l_;
    if (!q) memset(g[p], 0, sizeof(g[p])), f[p] = 0;
    else memcpy(g[p], g[q], sizeof(g[p])), f[p] = f[q];
    return p;
}

void clr() { nc = 0; gn(0); f[0] = -1; }

int extend(int p, int o, int i) {
    int np = gn(l[p] + 1); pos[np] = i; nid[i] = np;
    for (; p != -1 && !g[p][o]; p = f[p]) g[p][o] = np;
    if (p == -1) f[np] = 0;
    else {
        int q = g[p][o];
        if (l[q] == l[p] + 1) f[np] = q;
        else {
            int nq = gn(l[p] + 1, q);
            f[np] = f[q] = nq;
            for (; p != -1 && g[p][o] == q; p = f[p])
                g[p][o] = nq;
        }
    }
    return np;
}

vector<int> gt[N];
int dlb[N], drb[N], dfc;
void dfs_num(int u) {
    dlb[u] = ++dfc;
    for (int v : gt[u]) dfs_num(v);
    drb[u] = dfc;
}

int mp[N][20];
void mp_init() {
    f[0] = 0;
    for (int i = 0; i != nc; ++i)
        gt[i].clear();
    for (int i = 1; i != nc; ++i) {
        gt[f[i]].push_back(i);
        mp[i][0] = f[i];
    }

    for (int j = 1; (1 << j) < nc; ++j)
        for (int i = 0; i != nc; ++i)
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
}

int mp_find(int l1, int r1) {
    int p = nid[r1], len = r1 - l1 + 1;
    for (int i = 19; i >= 0; --i)
        if (l[mp[p][i]] >= len)
            p = mp[p][i];
    return p;
}


int val[M], ls[M], rs[M], rt[N], sc;
int cp(int p) {
    int q = ++sc;
    val[q] = val[p];
    ls[q] = ls[p];
    rs[q] = rs[p];
    return q;
}

void ins(int x, int p, int lb, int rb) {
    val[p]++;
    if (lb + 1 == rb) return;
    else {
        int mid = (lb + rb) >> 1;
        if (x < mid) ins(x, ls[p] = cp(ls[p]), lb, mid);
        else ins(x, rs[p] = cp(rs[p]), mid, rb);
    }
}

int query(int l, int r, int lp, int rp, int lb, int rb) {
    if (l <= lb && rb <= r) return val[rp] - val[lp];
    else {
        int mid = (lb + rb) >> 1, res = 0;
        if (l < mid) res += query(l, r, ls[lp], ls[rp], lb, mid);
        if (r > mid) res += query(l, r, rs[lp], rs[rp], mid, rb);
        return res;
    }
}

void solve(istream& cin, ostream& cout) {
    int n, q; string s;
    cin >> n >> q >> s;

    int p = 0; clr();
    for (int i = 0; i != s.size(); ++i) {
        int o = s[i] - 'a';
        p = extend(p, o, i + 1);
    }

    mp_init();
    dfc = 0; dfs_num(0);

    sc = 0;
    for (int i = 1; i <= s.size(); ++i)
        ins(dlb[nid[i]], rt[i] = cp(rt[i - 1]), 1, dfc + 1);

    while(q--) {
        int l1, r1, l2, r2, lv, rv;
        cin >> l1 >> r1 >> l2 >> r2;
        int res;
        if (r1 - l1 + 1 > r2 - l2 + 1)
            res = 0;
        else {
            p = mp_find(l1, r1);
            lv = l2 + (r1 - l1 + 1) - 1;
            rv = r2;
            res = query(dlb[p], drb[p] + 1, rt[lv - 1], rt[rv], 1, dfc + 1);
        }
        cout << res << endl;
    }
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif
    solve(cin, cout);
    return 0;
}