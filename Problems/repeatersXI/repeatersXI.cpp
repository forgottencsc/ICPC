#include <bits/stdc++.h>
#define N 2000001
using namespace std;

int g[N][26], f[N], l[N], w[N], nc;
int v[N], e[N]; bool vis[N];

int gn(int len, int q = 0) {
    int p = nc++; l[p] = len;
    if (!q) memset(g[p], 0, sizeof(g[p])), f[p] = 0;
    else memcpy(g[p], g[q], sizeof(g[p])), f[p] = f[q];
    return p;
}

void clr() { nc = 0; gn(0); f[0] = -1; }

int extend(int p, int o) {
    int np = gn(l[p] + 1); w[np] = 1;
    for (; p != -1 && !g[p][o]; p = f[p])
        g[p][o] = np;
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

int c[N], pos[N], ans[N];
void sort_sam(int n) {
    for (int i = 0; i != nc; ++i) c[l[i]]++;
    for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
    for (int i = 0; i != nc; ++i) pos[--c[l[i]]] = i;
}

void solve(istream& cin, ostream& cout) {
    string s; cin >> s;
    int n = s.size();
    int p = 0; clr();
    for (int i = 0; i != n; ++i)
        p = extend(p, s[i] - 'a');

    sort_sam(n);

    for (int i = nc - 1; i > 0; --i) {
        int p = pos[i];
        w[f[p]] += w[p];
        ans[l[p]] = max(ans[l[p]], w[p]);
    }

    for (int i = n; i > 0; --i)
        ans[i - 1] = max(ans[i - 1], ans[i]);

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    solve(cin,cout);
    return 0;
}