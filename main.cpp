
#include <bits/stdc++.h>
#define N 200001
#define M 20 * N
using namespace std;

typedef long long ll;

char s[N]; int n;
int g[N][26], f[N], l[N], pi[N], pv[N], sam_nc;
vector<int> gt[N];

int gn(int len, int q = 0){
    int p = sam_nc++; l[p] = len; gt[p].clear();
    if (!q) memset(g[p], 0, sizeof(g[p])), f[p] = 0;
    else memcpy(g[p], g[q], sizeof(g[p])), f[p] = f[q];
    return p;
}

void clr() {
    sam_nc = 0; gn(0); f[0] = -1;
}

int extend(int p, int o) {
    int np = gn(l[p] + 1);
    for (; p != -1 && !g[p][o]; p = f[p])
        g[p][o] = np;
    if (p == -1) f[np] = 0;
    else {
        int q = g[p][o];
        if (l[p] + 1 == l[q]) f[np] = q;
        else {
            int nq = gn(l[p] + 1, q);
            f[np] = f[q] = nq;
            for (; p != -1 && g[p][o] == q; p = f[p])
                g[p][o] = nq;
        }
    }
    return np;
}

int ls[M], rs[M], st[M], rt[N], pst_nc;
int cp(int q) {
    int p = ++pst_nc;
    ls[p] = ls[q];
    rs[p] = rs[q];
    st[p] = st[q];
    return p;
}

void modify(int x, int v, int p, int lb, int rb) {
    st[p] += v;
    if (lb + 1 == rb) return;
    else {
        int mid = (lb + rb) >> 1;
        if (x < mid) modify(x, v, ls[p] = cp(ls[p]), lb, mid);
        else modify(x, v, rs[p] = cp(rs[p]), mid, rb);
    }
}

int query(int k, int lp, int rp, int lb, int rb) {
    if (lb + 1 == rb) return lb;
    else {
        int mid = (lb + rb) >> 1;
        int lc = st[ls[rp]] - st[ls[lp]];
        if (k <= lc)
            return query(k, ls[lp], ls[rp], lb, mid);
        else
            return query(k - lc, rs[lp], rs[rp], mid, rb);
    }
}

int dlb[N], drb[N], dfc;
void dfs_build(int p) {
    dlb[p] = ++dfc;
    modify(pv[p], 1, rt[dfc] = cp(rt[dfc - 1]), 1, n + 1);
    for (int q : gt[p])
        dfs_build(q);
    drb[p] = dfc;
}

int mp[N][18];
void jmp_init() {
    f[0] = 0;

    for (int i = 1; i != sam_nc; ++i)
        mp[i][0] = f[i];

    for (int j = 1; (1 << j) < sam_nc; ++j)
        for (int i = 1; i <= sam_nc; ++i)
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
}

int jmp(int l1, int r1) {
    int p = pi[r1], len = r1 - l1 + 1;
    for (int j = 17; j >= 0; --j)
        if (l[mp[p][j]] >= len)
            p = mp[p][j];
    return p;
}

void solve(istream& cin, ostream& cout) {
    int q; cin >> n >> q >> s;
    clr(); int p = 0;
    for (int i = 0; i != n; ++i) {
        p = extend(p, s[i] - 'a');
        pi[i + 1] = p;
        pv[p] = i + 1;
    }

    for (int i = 0; i != sam_nc; ++i) {
        if (f[i] >= 0)
            gt[f[i]].push_back(i);
        if (!pv[i])
            pv[i] = n + 1;
    }

    dfc = 0;
    dfs_build(0);

    jmp_init();

    int ans = 0;
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int p = jmp(l, r), lv = dlb[p] - 1, rv = drb[p];
        ans = query(k, rt[lv], rt[rv], 1, n + 1);
        cout << ans - (r - l + 1) + 1 << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    solve(cin, cout);

    return 0;
}
